#include "CameraActor.h"

CameraActor::CameraActor(const Transform& pTransform, const float pFov, const float pNear, const float pFar):
    GameActor(pTransform, "CameraActor")
{
    AddComponent(new Camera(this, Transform::Origin, pFov, pNear, pFar));
}