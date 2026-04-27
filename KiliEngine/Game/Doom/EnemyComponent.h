#pragma once
#include "Engine/Components/ActorComponent.h"

class AnimatedComponent;

class EnemyComponent : public ActorComponent
{
private:
    AnimatedComponent* mSprite;
    float mLife;
    
protected:
    void OnStart() override;
    void OnUpdate() override {}
    
public:
    EnemyComponent(GameActor* pOwner);
    
    void TakeDamage(float pDamage);
    
};
