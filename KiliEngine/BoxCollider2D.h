#pragma once

#include "ColliderComponent.h"
#include "Struct.h"
using Struct::Rectangle;
using Struct::Vector2;

class BoxCollider2D : public ColliderComponent
{

private:
	Rectangle mBoxCollider; // center is local offset
	float mRadius;

public:

	BoxCollider2D(GameActor* owner, short updatePriority, Rectangle box) :
		ColliderComponent(owner, updatePriority),
		mBoxCollider(box)
	{
		mRadius = mBoxCollider.GetRadius();
	};

	~BoxCollider2D() = default;

	Rectangle GetBoxCollider() const { return mBoxCollider; };
	void SetBoxCollider(Rectangle rect) { 
		mBoxCollider = rect; mRadius = mBoxCollider.GetRadius(); 
	};

	float GetRadius() const { return mRadius; };

	Vector2 Collide(BoxCollider2D* other) const;
};

