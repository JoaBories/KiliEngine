#pragma once
#include "ActorComponent.h"
class ColliderComponent : public ActorComponent
{
public:
    ColliderComponent(GameActor* owner, short updateOrder = 50)
        : ActorComponent(owner, updateOrder)
    {
    }

    virtual ~ColliderComponent() = default;

    void Update() override {};
};

