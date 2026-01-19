#include "BoxCollider2D.h"
#include "GameActor.h"

using Struct::Vector2;

std::vector<BoxCollider2D*> BoxCollider2D::allBoxCollider = {};

void BoxCollider2D::OnStart()
{
}

void BoxCollider2D::Update()
{
	for (const auto& collider : allBoxCollider)
	{
		if (collider != this)
		{
			Vector2 overlap = mBoxCollider.toObjectSpace(mOwner.GetTransform()).CheckAABB(collider->GetBoxCollider().toObjectSpace(collider->GetOwner().GetTransform()));

			if (overlap != Vector2::zero)
			{
			}
		}
	}
}

void BoxCollider2D::OnEnd()
{
}

Rectangle BoxCollider2D::GetBoxCollider() const
{
	return mBoxCollider.toObjectSpace(mOwner.GetTransform());
}
