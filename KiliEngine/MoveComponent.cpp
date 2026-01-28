#include "MoveComponent.h"
#include "MathUtils.h"
#include "GameActor.h"
#include "Time.h"
#include "Log.h"

MoveComponent::MoveComponent(GameActor* pOwner, float pMaxVelocity, float pVelocityDecay, int pUpdateOrder) :
	ActorComponent(pOwner, pUpdateOrder),
	mVelocity(Vector2::zero),
	mVelocityDecay(pVelocityDecay), mMaxVelocity(pMaxVelocity)
{
}

void MoveComponent::SetVelocity(Vector2 pVelocity)
{
	mVelocity = pVelocity;
	mVelocity.clamp(0.0f, mMaxVelocity);
}

void MoveComponent::AddVelocity(Vector2 pVelocity)
{
	mVelocity += pVelocity;
	mVelocity.clamp(0.0f, mMaxVelocity);
}

void MoveComponent::Update()
{
	if (!MathUtils::NearZero(mVelocity.sqrLength()))
	{
		Transform2D ownTransform = mOwner->GetTransform();
		Vector2 newPos = ownTransform.position;
		newPos += ownTransform.Up() * mVelocity.y * Time::deltaTime;
		newPos += ownTransform.Right() * mVelocity.x * Time::deltaTime;
		mOwner->SetPosition(newPos);

		mVelocity *= mVelocityDecay;
	}
}
