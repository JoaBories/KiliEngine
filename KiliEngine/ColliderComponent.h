#pragma once
#include "ActorComponent.h"
class ColliderComponent : public ActorComponent
{
public:
    ColliderComponent(GameActor* owner, Transform transform, short updateOrder = 50)
        : ActorComponent(owner, transform, updateOrder)
    {
    }

    virtual ~ColliderComponent() = default;

    void OnUpdate() override {};
};

