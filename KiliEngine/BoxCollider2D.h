#pragma once

#include "ColliderComponent.h"
#include "Utils/Struct.h"
using Struct::Rectangle;
using Struct::Vector2;

class BoxCollider2D : public ColliderComponent
{

private:
	Rectangle mBoxCollider;
	float mRadius;

public:

	BoxCollider2D(GameActor* pOwner, const Transform& pTransform, const Rectangle& pBox, const short pUpdatePriority = 50) :
		ColliderComponent(pOwner, pTransform, pUpdatePriority),
		mBoxCollider(pBox)
	{
		mRadius = mBoxCollider.GetRadius();
	}

	~BoxCollider2D() = default;

	Rectangle GetBoxCollider() const { return mBoxCollider; }
	void SetBoxCollider(const Rectangle& pRect) { 
		mBoxCollider = pRect; mRadius = mBoxCollider.GetRadius(); 
	}
	
	float GetRadius() const { return mRadius; }

	Vector2 Collide(BoxCollider2D* pOther);
};

