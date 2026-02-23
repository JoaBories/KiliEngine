#pragma once
#include "ColliderComponent.h"

class BoxCollider : public ColliderComponent
{
private:
    Vector3 mHalfSize;
    float mRadius;
    
public:
    BoxCollider(GameActor* pOwner, const Transform& pTransform, const Vector3& pHalfSize, short pUpdateOrder = 50);
    //todo debug boxes
    Vector3 GetHalfSize() const {return mHalfSize;}
    void SetHalfSize(const Vector3& pHalfSize) {mHalfSize = pHalfSize;}
    
    float GetRadius() const {return mRadius;}
    
    Vector3 Collide(BoxCollider* pOther);
    
};
