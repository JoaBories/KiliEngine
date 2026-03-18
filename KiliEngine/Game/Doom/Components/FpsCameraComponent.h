#pragma once
#include "Engine/Components/ActorComponent.h"

class FpsCameraComponent : public ActorComponent
{
private:
    float mSensibility;
    Vector3 mPositionOffset;
    GameActor* mPlayer;

    void OnUpdate() override;

public:
    FpsCameraComponent(GameActor* pOwner, float pSensibility, const Vector3& pPositionOffset = Vector3(0, 0, 0));

    [[nodiscard]] Vector3 GetPositionOffset() const { return mPositionOffset; }
    void SetPositionOffset(const Vector3& pPositionOffset) { mPositionOffset = pPositionOffset; }

    [[nodiscard]] GameActor* GetPlayer() const { return mPlayer; }
    void SetPlayer(GameActor* pPlayer) { mPlayer = pPlayer; }
};
