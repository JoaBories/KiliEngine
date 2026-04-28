#include "EnemyComponent.h"

#include "Engine/GameActor.h"
#include "Engine/Components/AnimatedComponent.h"

void EnemyComponent::OnStart()
{
    mSprite = mOwner->GetComponent<AnimatedComponent>();
    mSprite->Play(true);
}

EnemyComponent::EnemyComponent(GameActor* pOwner) : ActorComponent(pOwner, Transform::Origin)
{
    SetName("EnemyComponent");
    mLife = 5.0f;
}

void EnemyComponent::TakeDamage(const float pDamage)
{
    mLife -= pDamage;
    if (mLife <= 0.0f) mOwner->Destroy();
}
