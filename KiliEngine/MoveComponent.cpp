#include "MoveComponent.h"
#include "Utils/MathUtils.h"
#include "GameActor.h"
#include "GameTime.h"
#include "Log.h"

MoveComponent::MoveComponent(GameActor* pOwner, const short pUpdateOrder) :
	ActorComponent(pOwner, Transform::Origin, pUpdateOrder),
	mVelocity(Vector3::zero)
{
}

void MoveComponent::SetVelocity(const Vector3& pVelocity)
{
	mVelocity = pVelocity;
}

void MoveComponent::AddVelocity(const Vector3& pVelocity)
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
