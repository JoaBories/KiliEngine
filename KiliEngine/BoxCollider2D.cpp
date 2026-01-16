#include "BoxCollider2D.h"
#include "GameActor.h"

void BoxCollider2D::OnStart()
{
}

void BoxCollider2D::Update()
{
}

void BoxCollider2D::OnEnd()
{
}

Rectangle BoxCollider2D::GetBoxCollider() const
{
	return mBoxCollider.toObjectSpace(mOwner.GetTransform());
}
