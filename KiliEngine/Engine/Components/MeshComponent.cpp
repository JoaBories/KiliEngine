#include "MeshComponent.h"

#include "Engine/Assets/AssetManager.h"
#include "Engine/Scene/SceneManager.h"

void MeshComponent::OnUpdate()
{
}

MeshComponent::MeshComponent(GameActor* pOwner, const Transform& pTransform, Mesh* pMesh, Texture* pTextureOverride, const std::string& pShaderOverride) :
	ActorComponent(pOwner, pTransform),
	mMesh(pMesh), mTextureOverride(pTextureOverride), mMaterialOverride(pShaderOverride)
{
	SetName("MeshComponent");
	SceneManager::ActiveScene()->GetRenderer()->AddMesh(this);
}

MeshComponent::~MeshComponent()
{
	SceneManager::ActiveScene()->GetRenderer()->RemoveMesh(this);
}

void MeshComponent::Draw(Camera* pCamera, Material* pMaterial)
{
	if (IsActive())
	{
		const Matrix4Row worldTransform = GetWorldTransform().GetWorldTransformMatrix();
	
		pMaterial->SetMatrix4Row("uViewProj", pCamera->GetViewProjMatrix());
		pMaterial->SetMatrix4Row("uWorldTransform", worldTransform);
		pMaterial->SetVec2("uTilling", GetWorldTransform().GetScale().y, GetWorldTransform().GetScale().x);

		if(const Texture* texture = GetTexture()) texture->SetActive();
	
		mMesh->GetVertexArray()->SetActive();
	
		glDrawArrays(GL_TRIANGLES, 0, mMesh->GetVertexArray()->GetVerticeCount());
	}
}

void MeshComponent::SetMesh(Mesh& pMesh)
{
	mMesh = &pMesh;
}

Texture* MeshComponent::GetTexture() const
{
	if (mTextureOverride) return mTextureOverride;
	return mMesh->GetTexture(0); 
}

std::string MeshComponent::GetMaterialName() const
{
	if (mMaterialOverride != "Null") return mMaterialOverride;
	return mMesh->GetMaterialName();
}

Material* MeshComponent::GetMaterial() const
{
	if (mMaterialOverride != "Null") return AssetManager::GetMaterial(mMaterialOverride);
	return mMesh->GetMaterial();
}

void MeshComponent::SetMaterialOverride(const std::string& pMaterialOverride)
{
	mMaterialOverride = pMaterialOverride;
	//todo change on renderer mesh vector
}
