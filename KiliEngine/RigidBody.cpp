#include "RigidBody.h"
#include "Config.h"
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