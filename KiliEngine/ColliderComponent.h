#pragma once
#include "ActorComponent.h"

class ColliderComponent : public ActorComponent
{
public:
    ColliderComponent(GameActor* pOwner, const Transform& pTransform, const short pUpdateOrder = 50);
    ~ColliderComponent() override;
    
    void OnUpdate() override {}

#ifdef _DEBUG
    virtual void Draw(const Matrix4Row& pViewProj) = 0;
#endif
};

