#pragma once
#include "ActorComponent.h"
#include "Mesh.h"

class MeshComponent : public ActorComponent
{
protected:
	Mesh* mMesh;
	size_t mTextureIndex;
public:
	MeshComponent(GameActor* pOwner, Transform pTransform);
	virtual ~MeshComponent();
	virtual void Draw(Matrix4Row viewProj);
	virtual void SetMesh(Mesh& pMesh);
	void SetTextureIndex(size_t pTextureIndex);
};

