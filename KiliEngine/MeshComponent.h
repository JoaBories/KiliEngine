#pragma once
#include "ActorComponent.h"
#include "Mesh.h"

class MeshComponent : public ActorComponent
{
protected:
	Mesh* mMesh;

	Texture* mTextureOverride;
	std::string mShaderOverride;
	
	void OnUpdate() override;
	
public:
	MeshComponent(GameActor* pOwner, const Transform& pTransform, Mesh* pMesh, Texture* pTextureOverride = nullptr, const std::string& pShaderOverride = "Null");
	~MeshComponent() override;
	
	virtual void Draw(const Matrix4Row& pViewProj, ShaderProgram* pShader);
	virtual void SetMesh(Mesh& pMesh); // todo doesn't support shader change after loading
	Mesh* GetMesh() const { return mMesh; }

	Texture* GetTexture() const;
	std::string GetShader() const;
	ShaderProgram* GetShaderProgram() const;
	
	void SetTextureOverride(Texture* pTextureOverride) { mTextureOverride = pTextureOverride; }
	Texture* GetTextureOverride() const { return mTextureOverride; }

	void SetShaderOverride(const std::string& pShaderOverride);
	std::string GetShaderOverride() const { return mShaderOverride; }

};