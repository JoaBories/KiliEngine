#pragma once
#include <vector>

#include "ColliderComponent.h"
#include "Engine/Assets/Mesh.h"

class BoxCollider : public ColliderComponent
{
protected:
    Vector3 mHalfSize;
    float mRadiusSq;
    
public:
    BoxCollider(GameActor* pOwner, const Transform& pTransform, bool pQuery, const Vector3& pHalfSize, short pUpdateOrder = 50);
    ~BoxCollider() override;
    
    Vector3 GetHalfSize() const {return mHalfSize;}
    void SetHalfSize(const Vector3& pHalfSize);
    
    float GetRadiusSq() const {return mRadiusSq;}

#ifdef _DEBUG

private:
    Mesh* mMesh;
    
public:    
    void Draw(const Matrix4Row& pViewProj) override;
#endif
};
