#pragma once
#include "Engine/Assets/Mesh.h"
#include "Engine/Components/ActorComponent.h"

class PlanetMeshComponent : public ActorComponent
{
private:
	Mesh* mPlanetMeshLod1;
	Mesh* mPlanetMeshLod0;

protected:
	void OnUpdate() override {};
	
public:
	PlanetMeshComponent(GameActor* pOwner, float pScale);
	~PlanetMeshComponent() override;

	void DrawFirst(Material* pMat);
	void DrawSecond(Material* pMat);
	
};
