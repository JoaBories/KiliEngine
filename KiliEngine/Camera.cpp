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
    const Vector3 camPosition = GetWorldTransform().GetPosition();
    const Vector3 target = GetWorldTransform().GetPosition() + GetWorldTransform().GetTransform().GetForwardVector() * 100.0f;
    mViewMatrix = Matrix4Row::CreateLookAt(camPosition, target, Vector3::unitZ);

    if (mProjNeedsUpdate)
    {
        mProjMatrix = Matrix4Row::CreatePerspectiveFOV(mFov, Cfg::WINDOW_WIDTH, Cfg::WINDOW_HEIGHT, mNearPane, mFarPane);
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

