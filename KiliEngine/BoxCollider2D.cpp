#include "BoxCollider2D.h"
#include "GameActor.h"

Vector2 BoxCollider2D::Collide(BoxCollider2D* other) const
{
	Vector2 pos = mOwner->GetTransform().position + mBoxCollider.center;
	Vector2 otherPos = other->GetOwner()->GetTransform().position +other->GetBoxCollider().center;

	if ((pos - otherPos).length() < mRadius + other->GetRadius())
	{
		Rectangle2 rect = mBoxCollider.toObjectSpace(mOwner->GetTransform());
		Rectangle2 otherRect = other->GetBoxCollider().toObjectSpace(other->GetOwner()->GetTransform());

		return rect.CheckAABB(otherRect);
	}

	return Vector2::zero;
}
