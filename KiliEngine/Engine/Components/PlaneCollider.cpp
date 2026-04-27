#include "PlaneCollider.h"

PlaneCollider::PlaneCollider(GameActor* pOwner, const Transform& pTransform, bool pQuery, const Vector2& pHalfSize) :
    BoxCollider(pOwner, pTransform, pQuery, Vector3(pHalfSize.x, pHalfSize.y, 0.01f))
{
}
