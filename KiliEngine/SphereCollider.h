#pragma once
#include <vector>

#include "ColliderComponent.h"
#include "Mesh.h"

class SphereCollider : public ColliderComponent
{
private:
    float mRadius;
    
public:
    SphereCollider(GameActor* pOwner, const Transform& pTransform, float pRadius, short pUpdateOrder = 50);
    void SetRadius(const float pRadius) { mRadius = pRadius; }
    float GetRadius() const { return mRadius; }  
    
    Vector3 Collide(SphereCollider* pOther);

#ifdef _DEBUG

private:
    Mesh* mMesh;
    
public:    
    void Draw(const Matrix4Row& pViewProj) override;
#endif
};