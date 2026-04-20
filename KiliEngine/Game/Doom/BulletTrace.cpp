#include "BulletTrace.h"

#include "Engine/Assets/AssetManager.h"
#include "Engine/Components/MeshComponent.h"
#include "Engine/Components/SphereCollider.h"

BulletTrace::BulletTrace(const CollisionUtils::Line& pLinetrace) :
        GameActor(Transform(
                (pLinetrace.End + pLinetrace.Start) * 0.5f, 
                Quaternion::QuaternionFromDirection(pLinetrace.Direction), 
                Vector3(pLinetrace.Length * 0.5f, 2.0f, 2.0f)), 
                "BulletTrace"),
        mTime(2.5f)
{
        AddComponent(new MeshComponent(this, Transform::Origin, AssetManager::GetMesh("BulletTrace")));
        //AddComponent(new SphereCollider(this, Transform::Origin , false, 1.0f));
}
