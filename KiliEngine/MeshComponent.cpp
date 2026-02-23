#include "MeshComponent.h"

#include "SceneManager.h"

void MeshComponent::OnUpdate()
{
}

MeshComponent::MeshComponent(GameActor* pOwner, const Transform& pTransform, Mesh* pMesh) :
	ActorComponent(pOwner, pTransform),
	mMesh(pMesh), mTextureIndex(0)
{
	SceneManager::ActiveScene()->GetRenderer()->AddMesh(this);
}

MeshComponent::~MeshComponent()
{
	SceneManager::ActiveScene()->GetRenderer()->RemoveMesh(this);
}

void MeshComponent::Draw(Matrix4Row pViewProj)
{
	const Matrix4Row worldTransform = GetWorldTransform().GetWorldTransformMatrix();
	
	mMesh->GetShaderProgram()->SetMatrix4Row("uViewProj", pViewProj);
	mMesh->GetShaderProgram()->SetMatrix4Row("uWorldTransform", worldTransform);
	
	const Texture* texture = mMesh->GetTexture(mTextureIndex);
	if(texture) texture->SetActive();
	
	mMesh->GetVertexArray()->SetActive();
	
	glDrawArrays(GL_TRIANGLES, 0, mMesh->GetVertexArray()->GetVerticeCount());
}

void MeshComponent::SetMesh(Mesh& pMesh)
{
	mMesh = &pMesh;
}

void MeshComponent::SetTextureIndex(const size_t pTextureIndex)
{
	mTextureIndex = pTextureIndex;
}
