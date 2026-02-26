#pragma once
#include "ActorComponent.h"

struct Collision
{
    bool Collided = false;
    Vector3 OverlapDir = Vector3(0, 0, 0);
    float OverlapLength = 0;

    explicit operator bool() const { return Collided; }
    [[nodiscard]] Vector3 Overlap() const { return OverlapDir * OverlapLength; }
};

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

