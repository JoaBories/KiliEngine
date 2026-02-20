#include "Camera.h"

#include "GameTime.h"
#include "Inputs.h"
#include "SceneManager.h"
#include "Window.h"

void Camera::OnStart()
{
    UseCamera();
}

void Camera::OnEarlyUpdate()
{
    if (Inputs::IsKeyPressed(SDLK_z))
    {
        AddPosition(GetWorldTransform().GetTransform().GetForwardVector() * 10 * GameTime::DeltaTime);
    }
    else if (Inputs::IsKeyPressed(SDLK_s))
    {
        AddPosition(GetWorldTransform().GetTransform().GetForwardVector() * -10 * GameTime::DeltaTime);
    }

    if (Inputs::IsKeyPressed(SDLK_d))
    {
        AddPosition(GetWorldTransform().GetTransform().GetRightVector() * 10 * GameTime::DeltaTime);
    }
    else if (Inputs::IsKeyPressed(SDLK_q))
    {
        AddPosition(GetWorldTransform().GetTransform().GetRightVector() * -10 * GameTime::DeltaTime);
    }

    Vector2 mouseDelta = Inputs::GetMouseDelta();

    if (mouseDelta != Vector2::zero)
    {
        AddRotation(Quaternion(GetWorldTransform().GetTransform().GetUpVector(), mouseDelta.x * 0.1f * GameTime::DeltaTime));
        AddRotation(Quaternion(GetWorldTransform().GetTransform().GetRightVector(), mouseDelta.y * 0.1f * GameTime::DeltaTime));
    }
    
    const Vector3 camPosition = GetWorldTransform().GetPosition();
    const Vector3 target = GetWorldTransform().GetPosition() + GetWorldTransform().GetTransform().GetForwardVector() * 100.0f;
    mViewMatrix = Matrix4Row::CreateLookAt(camPosition, target, Vector3::unitZ);

    if (mProjNeedsUpdate)
    {
        mProjMatrix = Matrix4Row::CreatePerspectiveFOV(mFov, Width, Height, mNearPane, mFarPane);
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

