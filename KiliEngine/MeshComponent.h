#pragma once
#include "ActorComponent.h"
#include "Mesh.h"

class MeshComponent : public ActorComponent
{
protected:
	Mesh* mMesh;
	size_t mTextureIndex;
	
	void OnUpdate() override;
	
public:
	MeshComponent(GameActor* pOwner, const Transform& pTransform, Mesh* pMesh);
	~MeshComponent() override;
	
	virtual void Draw(Matrix4Row pViewProj);
	virtual void SetMesh(Mesh& pMesh); // todo doesn't support shader change after loading
	Mesh* GetMesh() const { return mMesh; }
	void SetTextureIndex(size_t pTextureIndex);

};