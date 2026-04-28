#pragma once
#include "Engine/Assets/Mesh.h"
#include "Engine/Components/ActorComponent.h"

class PlanetMeshComponent : public ActorComponent
{
private:
	Mesh* mPlanetMeshLod1;
	Mesh* mPlanetMeshLod0;
	Texture* mSeaTexture;
	Texture* mGroundTexture;
	float mRotateSpeed;
	float mSeaLevel; // Between -1 (no sea) and 1 (everything is sea)
	float mReliefScale;

protected:
	void OnUpdate() override {}
	
public:
	PlanetMeshComponent(GameActor* pOwner, float pScale, Texture* pSeaTexture, Texture* pGroundTexture, float pRotateSpeed, float pSeaLevel, float pReliefScale);
	~PlanetMeshComponent() override;

	void DrawFirst(Material* pMat);
	void DrawSecond(Material* pMat);
	
};
