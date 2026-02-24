#include "Camera.h"

#include "GameTime.h"
#include "Inputs.h"
#include "SceneManager.h"
#include "Config.h"

void Camera::OnStart()
{
    UseCamera();
}

void Camera::OnEarlyUpdate()
{
    if (Inputs::IsKeyPressed(SDLK_z))
    {
        AddPosition(GetWorldTransform().GetTransform().GetForwardVector() * 20 * GameTime::DeltaTime);
    }
    else if (Inputs::IsKeyPressed(SDLK_s))
    {
        AddPosition(GetWorldTransform().GetTransform().GetForwardVector() * -20 * GameTime::DeltaTime);
    }

    if (Inputs::IsKeyPressed(SDLK_d))
    {
        AddPosition(GetWorldTransform().GetTransform().GetRightVector() * 20 * GameTime::DeltaTime);
    }
    else if (Inputs::IsKeyPressed(SDLK_q))
    {
        AddPosition(GetWorldTransform().GetTransform().GetRightVector() * -20 * GameTime::DeltaTime);
    }

    const Vector2 mouseDelta = Inputs::GetMouseDelta();
    if ( mouseDelta != Vector2::zero)
    {
        Vector3 currentEuler = mTransform.GetRotation().AsMatrixRow().GetEulerRotation();
        
        currentEuler.z += mouseDelta.x * 10 * GameTime::DeltaTime * MathUtils::DEG2RAD;
        currentEuler.y += mouseDelta.y * 10 * GameTime::DeltaTime * MathUtils::DEG2RAD;

        Quaternion newRotation = Quaternion(Vector3::unitZ, currentEuler.z) * Quaternion(Vector3::unitY, currentEuler.y) * Quaternion(Vector3::unitX, currentEuler.x); 
        SetRotation(newRotation);
    }
    
    const Vector3 camPosition = GetWorldTransform().GetPosition();
    const Vector3 target = GetWorldTransform().GetPosition() + GetWorldTransform().GetTransform().GetForwardVector() * 100.0f;
    mViewMatrix = Matrix4Row::CreateLookAt(camPosition, target, Vector3::unitZ);

    if (mProjNeedsUpdate)
    {
        mProjMatrix = Matrix4Row::CreatePerspectiveFOV(mFov, WINDOW_WIDTH, WINDOW_HEIGHT, mNearPane, mFarPane);
    }
}

void Camera::OnLateUpdate()
{
}

Camera::Camera() :
    GameActor(Transform::Origin),
    mProjNeedsUpdate(true),
    mFov(70.0f), mNearPane(0.1f), mFarPane(1000.0f)
{
}

Camera::Camera(const Transform& pTransform, const float pFov, const float pNear, const float pFar):
    GameActor(pTransform),
    mProjNeedsUpdate(true),
    mFov(pFov), mNearPane(pNear), mFarPane(pFar)
{
}

void Camera::UseCamera()
{
    SceneManager::ActiveScene()->GetRenderer()->SetCamera(this);
}

