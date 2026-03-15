#pragma once

#include "GameActor.h"
#include "MeshComponent.h"
#include "RigidBody.h"

constexpr float MaxForce = 3.0f;
constexpr float MinForce = 1.0f;

constexpr float MaxYaw = 45.0f;

constexpr float MaxY = 2.6f;

class BowlingBall : public GameActor // Just an actor that will store a mesh component
{
private:
    MeshComponent* mArrow;
    MeshComponent* mBall;
    RigidBody* mRb;
    float mForce = 1.0f;
    bool mLaunched = false;
    float mYaw = 0.0f;
    
    void UpdateArrow() const;
    
public:
    BowlingBall(const Transform& pTransform) :
        GameActor(pTransform)
    {
    }

protected:
    void OnLateUpdate() override;
    void OnStart() override;
};
