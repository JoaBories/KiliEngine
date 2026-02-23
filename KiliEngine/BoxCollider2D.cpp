#include "BoxCollider2D.h"
#include "GameActor.h"
#include "Vector3.h"

Vector2 BoxCollider2D::Collide(BoxCollider2D* pOther)
{
	const Vector3 pos = GetWorldTransform().GetPosition();
	const Vector3 otherPos = pOther->GetWorldTransform().GetPosition();

	if ((pos - otherPos).Length() < mRadius + pOther->GetRadius())
	{
		const Rectangle rect = mBoxCollider.toObjectSpace(GetWorldTransform().GetTransform());
		const Rectangle otherRect = pOther->GetBoxCollider().toObjectSpace(pOther->GetWorldTransform().GetTransform());

		return rect.CheckOBB(otherRect);
	}

	return Vector2::zero;
}
