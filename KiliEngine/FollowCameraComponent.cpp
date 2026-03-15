#include "FollowCameraComponent.h"

#include <algorithm>

#include "GameActor.h"

FollowCameraComponent::FollowCameraComponent(GameActor* pOwner, GameActor* pTarget, 
                                             const LockAxis pPositionLock, const Vector3& pPositionOffset, const Vector3& pTargetOffset) :

    ActorComponent(pOwner, Transform::Origin), 
    mPositionOffset(pPositionOffset), mTargetOffset(pTargetOffset), 
    mTargetActor(pTarget), 
    mPositionLock(pPositionLock)
{
}

void FollowCameraComponent::OnUpdate()
{
    Vector3 position = mOwner->GetWorldTransform().GetPosition();
    Vector3 targetPosition = mTargetActor->GetWorldTransform().GetPosition() + mTargetOffset;
    Vector3 newPos = targetPosition + mPositionOffset;
    newPos = Vector3(
        MathUtils::Lerp(position.x, newPos.x, (mPositionLock.X) ? 0.0f : 0.05f),
        MathUtils::Lerp(position.y, newPos.y, (mPositionLock.Y) ? 0.0f : 0.05f),
        MathUtils::Lerp(position.z, newPos.z, (mPositionLock.Z) ? 0.0f : 0.05f)
        );
    
    mOwner->SetPosition(newPos);
    
    Vector3 lookAtVector = (targetPosition - newPos).Normalized();

    float halfAngle      = MathUtils::ACos(Vector3::Dot(Vector3::unitX, lookAtVector)) * 0.5f;
    Vector3 rotationAxis = Vector3::Cross(Vector3::unitX, lookAtVector).Normalized();
    Vector3 quatImg      = rotationAxis * MathUtils::Sin(halfAngle);

    Quaternion lookAtRotation = Quaternion(quatImg.x, quatImg.y, quatImg.z, MathUtils::Cos(halfAngle));
    mOwner->SetRotation(lookAtRotation);
}
