#pragma once
#include <vector>

#include "ColliderComponent.h"
#include "Mesh.h"

class BoxCollider : public ColliderComponent
{
private:
    Vector3 mHalfSize;
    float mRadius;

    std::vector<Vector3> GetCorners();
    
public:
    BoxCollider(GameActor* pOwner, const Transform& pTransform, const Vector3& pHalfSize, short pUpdateOrder = 50);
    ~BoxCollider() override;
    
    Vector3 GetHalfSize() const {return mHalfSize;}
    void SetHalfSize(const Vector3& pHalfSize) {mHalfSize = pHalfSize;}
    
    float GetRadius() const {return mRadius;}

#ifdef _DEBUG

private:
    Mesh* mMesh;
    
public:    
    void Draw(const Matrix4Row& pViewProj) override;
#endif
};
