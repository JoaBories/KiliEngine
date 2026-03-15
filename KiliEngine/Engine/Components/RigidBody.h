#pragma once
#include "MoveComponent.h"
#include "ColliderComponent.h"

class RigidBody : public MoveComponent
{
private:
    float mGravityScale;
    float mLinearDamping;
    float mMass;
    float mRestitution;
    
public:
    explicit RigidBody(GameActor* pOwner, float pLinearDamping = 0.0f, float pGravity = 1.0f, float pMass = 1.0f, float pRestitution = 0.5f);
    
    void OnUpdate() override;

    void OnCollide(const Collision& pCollision, const ColliderComponent* pOtherCollider);
    
    [[nodiscard]] float GetRestitution() const { return mRestitution; }
    void SetRestitution(const float pRestitution) { mRestitution = pRestitution; }

    [[nodiscard]] float GetGravityScale() const { return mGravityScale; }
    void SetGravityScale(const float pGravityScale) { mGravityScale = pGravityScale; }

    [[nodiscard]] float GetLinearDamping() const { return mLinearDamping; }
    void SetDamping(const float pLinearDamping) { mLinearDamping = pLinearDamping; }

    [[nodiscard]] float GetMass() const { return mMass; }
    void SetMass(const float pMass) { mMass = pMass; }
};