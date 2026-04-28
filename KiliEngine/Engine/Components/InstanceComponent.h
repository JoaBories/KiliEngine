#pragma once
#include "MeshComponent.h"

class InstanceComponent : public MeshComponent
{
protected:
    Vector2 mSize;
    int mCount;

    void OnUpdate() override;

public:
    InstanceComponent() = delete;
    InstanceComponent(GameActor* pOwner, const Transform& pTransform, Mesh* pMesh, const Vector2& pSize, int pCount, Texture* pTextureOverride = nullptr);

    void Draw(Material* pMaterial) override;
    
};
