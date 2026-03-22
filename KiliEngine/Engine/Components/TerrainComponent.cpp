#include "TerrainComponent.h"

TerrainComponent::TerrainComponent(GameActor* pOwner, const Transform& pTransform, Texture* pTexture, Texture* pHeightMap, 
    float pSquareSize, int pSquareNumber, const std::string& pMaterialOverride) :
    ActorComponent(pOwner, pTransform),
    mTexture(pTexture), mHeightMap(pHeightMap)
{
    if (pMaterialOverride != "Null") mMaterialName = pMaterialOverride;
    else mMaterialName = "TerrainTess";

    for (int i = 0; i < pSquareNumber; ++i)
    {
        
    }
}

TerrainComponent::~TerrainComponent()
{
}

void TerrainComponent::Draw(Camera* pCamera, Material* pMaterial)
{
}
