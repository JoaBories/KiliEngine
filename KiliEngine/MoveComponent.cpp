#include "MoveComponent.h"
#include "Utils/MathUtils.h"
#include "GameActor.h"
#include "GameTime.h"
#include "Log.h"

MoveComponent::MoveComponent(GameActor* pOwner, Transform pTransform, int pUpdateOrder) :
	ActorComponent(pOwner, pTransform, pUpdateOrder),
	mVelocity(Vector3::zero)
{
}

void MoveComponent::SetVelocity(Vector3 pVelocity)
{
	mVelocity = pVelocity;
}

void MoveComponent::AddVelocity(Vector3 pVelocity)
{
	mVelocity += pVelocity;
}

void MoveComponent::OnUpdate()
{
	if (!MathUtils::NearZero(mVelocity.LengthSq()))
	{
		Vector3 displacement;
		displacement += mVelocity * GameTime::DeltaTime;
		GetOwner()->AddPosition(displacement);
	}
}
