#pragma once
#include "ActorComponent.h"
#include "Engine/Camera.h"
#include "Engine/VertexArray.h"
#include "Engine/Assets/AssetManager.h"
#include "Engine/Assets/Material.h"
#include "Engine/Assets/Texture.h"

class TerrainComponent : public ActorComponent
{
private:
    VertexArray* mVao;
    Texture* mTexture;
    Texture* mHeightMap;
    std::string mMaterialName;

public:
    TerrainComponent() = delete;
    TerrainComponent(GameActor* pOwner, const Transform& pTransform, Texture* pTexture, Texture* pHeightMap, float pSquareSize = 5, int pSquareNumber = 4, const std::string& pMaterialOverride = "Null");
    ~TerrainComponent() override;
    
    virtual void Draw(Camera* pCamera, Material* pMaterial);
    
    VertexArray* GetVao() const     { return mVao; }
    
    Texture* GetTexture() const     { return mTexture; }
    Texture* GetHeightMap() const   { return mHeightMap; }
    
    std::string GetMaterialName() const  { return mMaterialName; }
    Material* GetMaterial() const    { return AssetManager::GetMaterial(mMaterialName); }
};
