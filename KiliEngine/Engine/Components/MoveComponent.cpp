#include "MoveComponent.h"
#include "Utils/MathUtils.h"
#include "Engine/GameActor.h"
#include "Engine/Tools/GameTime.h"
#include "Engine/Tools/Log.h"

MoveComponent::MoveComponent(GameActor* pOwner, const short pUpdateOrder) :
	ActorComponent(pOwner, Transform::Origin, pUpdateOrder),
	mVelocity(Vector3::zero)
{
	SetName("MoveComponent");
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
