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
    std::string mMaterialName;
    float mHeightScale;

    static VertexArray* CreateTerrainVao(int pSquareNumber, float pSquareSize);
    
protected:
    void OnUpdate() override {}

public:
    TerrainComponent() = delete;
    TerrainComponent(GameActor* pOwner, const Transform& pTransform, Texture* pTexture, float pHeightScale = 0.5f, float pSquareSize = 5.0f, int pSquareNumber = 4, const std::string& pMaterialOverride = "Null");
    ~TerrainComponent() override;
    
    virtual void Draw(Camera* pCamera, Material* pMaterial);
    
    VertexArray* GetVao() const     { return mVao; }
    
    Texture* GetTexture() const     { return mTexture; }
    
    std::string GetMaterialName() const  { return mMaterialName; }
    Material* GetMaterial() const    { return AssetManager::GetMaterial(mMaterialName); }
};
