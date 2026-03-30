#include "RigidBody.h"
#include "Engine/Config.h"
#include "Engine/GameActor.h"
#include "Engine/Tools/GameTime.h"

RigidBody::RigidBody(GameActor* pOwner, const float pLinearDamping, const float pGravity, const float pMass, const float pRestitution) :
    MoveComponent(pOwner),
    mGravityScale(pGravity), mLinearDamping(pLinearDamping), mMass(pMass), mRestitution(pRestitution)
{
    SetName("RigidBody");
}

void RigidBody::OnUpdate()
{
    Vector3 velocity = GetVelocity();
    
    velocity += Cfg::GRAVITY_DIR * Cfg::GRAVITY_FORCE * mGravityScale * GameTime::DeltaTime;  //Gravity

    //Linear Damping
    const Vector3 downVelocity = Vector3::Dot(velocity, Cfg::GRAVITY_DIR) * Cfg::GRAVITY_DIR;
    velocity = (velocity - downVelocity) * (1.0f - mLinearDamping * GameTime::DeltaTime) + downVelocity;

    SetVelocity(velocity);
    
    MoveComponent::OnUpdate();
}

void RigidBody::OnCollide(const Collision& pCollision, const ColliderComponent* pOtherCollider)
{
    mOwner->AddPosition(pCollision.OverlapDir * Cfg::CORRECTION_STRENGTH * MathUtils::Max(pCollision.OverlapLength - Cfg::ALLOWED_PENETRATION, 0.0f));

    const RigidBody* otherRb = pOtherCollider->GetOwner()->GetComponent<RigidBody>();

    const Vector3 velocityB = otherRb ? otherRb->GetVelocity() : Vector3::zero;

    const float normalVelocity = Vector3::Dot(velocityB - mVelocity, -pCollision.OverlapDir);

    if (normalVelocity >= 0) return;

    const float massB = otherRb ? otherRb->GetMass() : 0.0f;
    const float restitutionB = otherRb ? otherRb->GetRestitution() : 1.0f;

    const float invMassA = 1 / mMass;
    const float invMassB = (massB > 0.0f) ? 1.0f / massB : 0.0f;

    const float force = -(1.0f + mRestitution * restitutionB) * normalVelocity / (invMassA + invMassB);
    
    AddVelocity(force * pCollision.OverlapDir * invMassA);
}
