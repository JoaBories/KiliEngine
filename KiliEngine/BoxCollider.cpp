#include "BoxCollider.h"

BoxCollider::BoxCollider(GameActor* pOwner, const Transform& pTransform, const Vector3& pHalfSize, const short pUpdateOrder) :
    ColliderComponent(pOwner, pTransform, pUpdateOrder),
    mHalfSize(pHalfSize), mRadius(0.0f)
{
    mRadius = mHalfSize.Length();
}

Vector3 BoxCollider::Collide(BoxCollider* pOther)
{
    Vector3 overlap = Vector3::zero;
    // todo implement collision between obb
    return overlap;
}
