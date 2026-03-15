#pragma once
#include "ActorComponent.h"
#include "CollisionUtils.h"

using namespace CollisionUtils;

class ColliderComponent : public ActorComponent
{
protected:
    bool mCollided = false;
    
public:
    ColliderComponent(GameActor* pOwner, const Transform& pTransform, const short pUpdateOrder = 50);
    ~ColliderComponent() override;
    
    void OnUpdate() override {}
    virtual void OnCollide(Collision pColl, ColliderComponent* pOtherCollider);

#ifdef _DEBUG
    virtual void Draw(const Matrix4Row& pViewProj) = 0;
#endif
};

