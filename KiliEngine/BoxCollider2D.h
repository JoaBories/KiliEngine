#pragma once

#include "ColliderComponent.h"
#include "Struct.h"
using Struct::Rectangle2;
using Struct::Vector2;

class BoxCollider2D : public ColliderComponent
{

private:
	Rectangle2 mBoxCollider; // center is local offset
	float mRadius;

public:

	BoxCollider2D(GameActor* owner, short updatePriority, Rectangle2 box) :
		ColliderComponent(owner, updatePriority),
		mBoxCollider(box)
	{
		mRadius = mBoxCollider.GetRadius();
	};

	~BoxCollider2D() = default;

	Rectangle2 GetBoxCollider() const { return mBoxCollider; };
	void SetBoxCollider(Rectangle2 rect) { 
		mBoxCollider = rect; mRadius = mBoxCollider.GetRadius(); 
	};

	float GetRadius() const { return mRadius; };

	Vector2 Collide(BoxCollider2D* other) const;
};

