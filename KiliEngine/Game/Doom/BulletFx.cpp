#include "BulletFx.h"

#include "Engine/Assets/AssetManager.h"
#include "Engine/Components/AnimatedComponent.h"
#include "Engine/Components/BillboardComponent.h"
#include "Engine/Tools/GameTime.h"

void BulletFx::OnEarlyUpdate()
{
    mTime -= GameTime::DeltaTime;

    if (mTime < 0.0f)
    {
        Destroy();
    }
}

BulletFx::BulletFx(const Transform& pTransform) :
    GameActor(pTransform, "BulletFx"), mTime(0.75f)
{
    AddComponent(new BillboardComponent(this, Transform(Vector3::zero, Quaternion(), Vector3(2.0f, 0.0f, 2.0f)), AssetManager::GetTexture("Impact_0")));
    AddComponent(new AnimatedComponent(this, AssetManager::GetAnimation("Impact", 0, 2, 4)));
    GetComponent<AnimatedComponent>()->Play(false);
}
