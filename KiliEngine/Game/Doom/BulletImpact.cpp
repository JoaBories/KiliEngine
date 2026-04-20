#include "BulletImpact.h"

#include "Engine/Assets/AssetManager.h"
#include "Engine/Components/MeshComponent.h"
#include "Engine/Tools/GameTime.h"

void BulletImpact::OnEarlyUpdate()
{
	mTime -= GameTime::DeltaTime;

	if (mTime < 0.0f)
	{
		Destroy();
	}
}

BulletImpact::BulletImpact(const Transform& pTransform) :
	GameActor(pTransform, "BulletImpact"),
	mTime(60.0f)
{
	AddComponent(new MeshComponent(this, Transform::Origin, AssetManager::GetMesh("plane"), AssetManager::GetTexture("BulletImpact"), "Decals"));
}
