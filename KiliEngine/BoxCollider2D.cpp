#include "BoxCollider2D.h"
#include "GameActor.h"
#include "Vector3.h"

Vector2 BoxCollider2D::Collide(BoxCollider2D* other)
{
	const Vector3 pos = GetWorldTransform().GetPosition();
	const Vector3 otherPos = other->GetWorldTransform().GetPosition();

	if ((pos - otherPos).Length() < mRadius + other->GetRadius())
	{
		const Rectangle rect = mBoxCollider.toObjectSpace(GetWorldTransform().GetTransform());
		const Rectangle otherRect = other->GetBoxCollider().toObjectSpace(other->GetWorldTransform().GetTransform());

		return rect.CheckOBB(otherRect);
	}

	return Vector2::zero;
}
