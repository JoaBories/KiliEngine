#pragma once
#include "BoxCollider.h"

class PlaneCollider : public BoxCollider
{
public:
    PlaneCollider(GameActor* pOwner, const Transform& pTransform, bool pQuery, const Vector2& pHalfSize);    
};
