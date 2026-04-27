#include "Camera.h"

#include "Scene/SceneManager.h"
#include "Config.h"

void Camera::OnStart()
{
    UseCamera();
}

void Camera::OnUpdate()
{
    const Vector3 camPosition = GetWorldTransform().GetPosition();
    const Vector3 target = GetWorldTransform().GetPosition() + GetWorldTransform().GetTransform().GetForwardVector() * 100.0f;
    mViewMatrix = Matrix4Row::CreateLookAt(camPosition, target, Vector3::unitZ);
    
    Vector2 screenSize = SceneManager::ActiveScene()->GetRenderer()->GetWindow()->GetDimensions();
    mProjMatrix = Matrix4Row::CreatePerspectiveFOV(mFov, screenSize.x, screenSize.y, mNearPane, mFarPane);
}

Camera::Camera(GameActor* pOwner, const Transform& pTransform, const float pFov, const float pNear, const float pFar):
    ActorComponent(pOwner, pTransform),
    mFov(pFov), mNearPane(pNear), mFarPane(pFar)
{
    SetName("Camera");
}

void Camera::UseCamera()
{
    SceneManager::ActiveScene()->GetRenderer()->SetCamera(this);
}

