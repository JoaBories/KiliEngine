#include "MeshComponent.h"

#include "Engine/Assets/AssetManager.h"
#include "Engine/Scene/SceneManager.h"

void MeshComponent::OnUpdate()
{
}

MeshComponent::MeshComponent(GameActor* pOwner, const Transform& pTransform, Mesh* pMesh, Texture* pTextureOverride, const std::string& pShaderOverride) :
	ActorComponent(pOwner, pTransform),
	mMesh(pMesh), mTextureOverride(pTextureOverride), mShaderOverride(pShaderOverride)
{
	SetName("MeshComponent");
	SceneManager::ActiveScene()->GetRenderer()->AddMesh(this);
}

MeshComponent::~MeshComponent()
{
	SceneManager::ActiveScene()->GetRenderer()->RemoveMesh(this);
}

void MeshComponent::Draw(Camera* pCamera, ShaderProgram* pShader)
{
	if (IsActive())
	{
		const Matrix4Row worldTransform = GetWorldTransform().GetWorldTransformMatrix();
	
		pShader->SetMatrix4Row("uViewProj", pCamera->GetViewProjMatrix());
		pShader->SetMatrix4Row("uWorldTransform", worldTransform);
		pShader->SetVec2("uTilling", GetWorldTransform().GetScale().y, GetWorldTransform().GetScale().x);

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

std::string MeshComponent::GetShader() const
{
	if (mShaderOverride != "Null") return mShaderOverride;
	return mMesh->GetShaderName();
}

ShaderProgram* MeshComponent::GetShaderProgram() const
{
	if (mShaderOverride != "Null") return AssetManager::GetShader(mShaderOverride);
	return mMesh->GetShaderProgram();
}

void MeshComponent::SetShaderOverride(const std::string& pShaderOverride)
{
	mShaderOverride = pShaderOverride;
	//todo change on renderer mesh vector
}
