#include "PlaneCollider.h"

PlaneCollider::PlaneCollider(GameActor* pOwner, const Transform& pTransform, const Vector2& pHalfSize) :
    BoxCollider(pOwner, pTransform, Vector3(pHalfSize.x, pHalfSize.y, 0.01f))
{
}
