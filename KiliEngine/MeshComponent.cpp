#include "MeshComponent.h"

#include "AssetManager.h"
#include "SceneManager.h"

void MeshComponent::OnUpdate()
{
}

MeshComponent::MeshComponent(GameActor* pOwner, const Transform& pTransform, Mesh* pMesh, Texture* pTextureOverride, const std::string& pShaderOverride) :
	ActorComponent(pOwner, pTransform),
	mMesh(pMesh), mTextureOverride(pTextureOverride), mShaderOverride(pShaderOverride)
{
	SceneManager::ActiveScene()->GetRenderer()->AddMesh(this);
}

MeshComponent::~MeshComponent()
{
	SceneManager::ActiveScene()->GetRenderer()->RemoveMesh(this);
}

void MeshComponent::Draw(const Matrix4Row& pViewProj, ShaderProgram* pShader)
{
	const Matrix4Row worldTransform = GetWorldTransform().GetWorldTransformMatrix();
	
	pShader->SetMatrix4Row("uViewProj", pViewProj);
	pShader->SetMatrix4Row("uWorldTransform", worldTransform);

	if(const Texture* texture = GetTexture()) texture->SetActive();
	
	mMesh->GetVertexArray()->SetActive();
	
	glDrawArrays(GL_TRIANGLES, 0, mMesh->GetVertexArray()->GetVerticeCount());
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
