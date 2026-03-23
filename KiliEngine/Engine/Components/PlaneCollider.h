#pragma once
#include "BoxCollider.h"

class PlaneCollider : public BoxCollider
{
public:
    PlaneCollider(GameActor* pOwner, const Transform& pTransform, const Vector2& pHalfSize);    
};
