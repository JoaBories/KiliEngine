#pragma once
#include "ActorComponent.h"
#include "Engine/Camera.h"
#include "Engine/Assets/Mesh.h"

class MeshComponent : public ActorComponent
{
protected:
    Mesh* mMesh;

    Texture* mTextureOverride;
    std::string mMaterialOverride;
	
    void OnUpdate() override;
	
	virtual void CleanUp() {}
	
public:
	MeshComponent() = delete;
    MeshComponent(GameActor* pOwner, const Transform& pTransform, Mesh* pMesh, Texture* pTextureOverride = nullptr, const std::string& pMaterialOverride = "Null");
    ~MeshComponent() override;
	
    virtual void Draw(Material* pMaterial);
    virtual void SetMesh(Mesh& pMesh); // todo doesn't support shader change after loading
    Mesh* GetMesh() const { return mMesh; }

    Texture* GetTexture() const;
    std::string GetMaterialName() const;
    Material* GetMaterial() const;
	
    void SetTextureOverride(Texture* pTextureOverride) { mTextureOverride = pTextureOverride; }
    Texture* GetTextureOverride() const { return mTextureOverride; }

    void SetMaterialOverride(const std::string& pMaterialOverride);
    std::string GetShaderOverride() const { return mMaterialOverride; }

};