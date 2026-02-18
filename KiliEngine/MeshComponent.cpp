#include "MeshComponent.h"

MeshComponent::MeshComponent(GameActor* pOwner, Transform pTransform) :
	ActorComponent(pOwner, pTransform),
	mMesh(nullptr), mTextureIndex(0)
{
}

MeshComponent::~MeshComponent()
{
}

void MeshComponent::Draw(Matrix4Row viewProj)
{
}

void MeshComponent::SetMesh(Mesh& pMesh)
{
}

void MeshComponent::SetTextureIndex(size_t pTextureIndex)
{
}
