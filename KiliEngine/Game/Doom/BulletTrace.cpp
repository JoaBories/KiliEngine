#include "BulletTrace.h"

#include "Engine/Assets/AssetManager.h"
#include "Engine/Components/MeshComponent.h"
#include "Engine/Components/SphereCollider.h"
#include "Engine/Tools/GameTime.h"

void BulletTrace::OnEarlyUpdate()
{
    const Vector3 scale = GetWorldTransform().GetScale() * (1.0f - 7.5f * GameTime::DeltaTime);
    SetScale(Vector3(scale.x, scale.y, GetWorldTransform().GetScale().z));

    if (scale.x <= 0.1f)
    {
        Destroy();
    }
}

BulletTrace::BulletTrace(const Line& pLinetrace) :
    GameActor(Transform(
        (pLinetrace.End + pLinetrace.Start) * 0.5f, 
        Quaternion::QuaternionFromDirection(pLinetrace.Direction), 
        Vector3(2.0f, 2.0f, pLinetrace.Length)), 
        "BulletTrace")
{
    AddComponent(new MeshComponent(this, Transform::Origin, AssetManager::GetMesh("BulletTrace"), AssetManager::GetTexture("BulletTrace")));
}