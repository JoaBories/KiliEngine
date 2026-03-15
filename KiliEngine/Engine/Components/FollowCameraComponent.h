#pragma once
#include "ActorComponent.h"

struct LockAxis
{
    bool X = false, Y = false, Z = false;
};

class FollowCameraComponent : public ActorComponent
{
protected:
    Vector3 mPositionOffset;
    Vector3 mTargetOffset;
    GameActor* mTargetActor;
    LockAxis mPositionLock;
    
public:
    FollowCameraComponent(GameActor* pOwner, GameActor* pTarget, 
        LockAxis pPositionLock = LockAxis(), 
        const Vector3& pPositionOffset = Vector3::zero, const Vector3& pTargetOffset = Vector3::zero);
    
    [[nodiscard]] Vector3 GetPositionOffset() const { return mPositionOffset; }
    void SetPositionOffset(const Vector3& pPositionOffset) { mPositionOffset = pPositionOffset; }

    [[nodiscard]] Vector3 GetTargetOffset() const { return mTargetOffset; }
    void SetTargetOffset(const Vector3& pTargetOffset) { mTargetOffset = pTargetOffset; }

    [[nodiscard]] GameActor* GetTargetActor() const { return mTargetActor; }
    void SetTargetActor(GameActor* pTargetActor) { mTargetActor = pTargetActor; }

    [[nodiscard]] LockAxis GetPositionLock() const { return mPositionLock; }
    void SetPositionLock(const LockAxis& pPositionLock) { mPositionLock = pPositionLock; }

protected:
    void OnUpdate() override;
};
