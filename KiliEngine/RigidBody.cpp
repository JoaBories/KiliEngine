#include "RigidBody.h"
#include "Config.h"
#include "GameActor.h"
#include "GameTime.h"

RigidBody::RigidBody(GameActor* pOwner, const float pLinearDamping, const float pGravity, const float pMass):
    MoveComponent(pOwner),
    mGravityScale(pGravity), mLinearDamping(pLinearDamping), mMass(pMass)
{
}

void RigidBody::OnUpdate()
{
    Vector3 velocity = GetVelocity();
    
    velocity += GRAVITY_DIR * GRAVITY_FORCE * mGravityScale * GameTime::DeltaTime;  //Gravity
    velocity *= (1.0f - mLinearDamping * GameTime::DeltaTime);                      //Linear Damping

    SetVelocity(velocity);
    
    MoveComponent::OnUpdate();
}

void RigidBody::OnCollide(const Collision& pCollision, ColliderComponent* pOtherCollider)
{
    mOwner->AddPosition(pCollision.Overlap());
    SetVelocity(Vector3::zero);
    
    Log::Info("x : " + std::to_string(pCollision.Overlap().x) + " , y: " + std::to_string(pCollision.Overlap().y) + " , z: " + std::to_string(pCollision.Overlap().z));
}
