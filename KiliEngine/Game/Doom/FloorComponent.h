#pragma once
#include "Engine/Components/MeshComponent.h"

class FloorComponent : public MeshComponent
{
protected:
    void OnUpdate() override;

    void CleanUp() override;

public:
    FloorComponent() = delete;
    FloorComponent(GameActor* pOwner, const Transform& pTransform, Mesh* pFloorMesh);

    void Draw(Material* pMaterial) override;
    
};
