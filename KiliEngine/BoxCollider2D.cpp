#include "BoxCollider2D.h"
#include "GameActor.h"
#include "Vector3.h"

Vector2 BoxCollider2D::Collide(BoxCollider2D* other)
{
	Vector3 pos = GetWorldTransform().GetPosition();
	Vector3 otherPos = other->GetWorldTransform().GetPosition();

	if ((pos - otherPos).Length() < mRadius + other->GetRadius())
	{
		Rectangle rect = mBoxCollider.toObjectSpace(GetWorldTransform());
		Rectangle otherRect = other->GetBoxCollider().toObjectSpace(other->GetWorldTransform());

		return rect.CheckOBB(otherRect);
	}

	return Vector2::zero;
}
