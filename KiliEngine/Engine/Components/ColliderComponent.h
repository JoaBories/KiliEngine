#pragma once
#include "ActorComponent.h"
#include "Utils/CollisionUtils.h"

using namespace CollisionUtils;

class ColliderComponent : public ActorComponent
{
    bool mQuery;
    
public:
    ColliderComponent(GameActor* pOwner, const Transform& pTransform, bool pQuery, short pUpdateOrder = 50);
    ~ColliderComponent() override;
    
    void OnUpdate() override {}
    virtual void OnCollide(Collision pColl, ColliderComponent* pOtherCollider);

    bool IsQuery() const { return mQuery; }

#ifdef _DEBUG
protected:
    bool mCollided = false;
    
public:
    virtual void Draw(const Matrix4Row& pViewProj) = 0;
#endif
};

