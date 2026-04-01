#pragma once
#include "MeshComponent.h"

class InstanceComponent : public MeshComponent
{
protected:
    Vector2 mSize;

public:
    InstanceComponent() = delete;
    InstanceComponent(GameActor* pOwner, const Transform& pTransform, Mesh* pMesh, const Vector2& pSize, Texture* pTextureOverride = nullptr);

    void Draw(Camera* pCamera, Material* pMaterial) override;
    
};
