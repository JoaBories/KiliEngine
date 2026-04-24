#include "DoorComponent.h"

#include "Engine/GameActor.h"
#include "Engine/Tools/GameTime.h"

void DoorComponent::OnUpdate()
{
    if (mGoingUp)
    {
        const float t = 1.0f - pow(mInterpSpeed, GameTime::DeltaTime);
        mOwner->SetPosition(Vector3::Lerp(mOwner->GetWorldTransform().GetPosition(), mGoalPosition, t));
        
        if ((mOwner->GetWorldTransform().GetPosition() - mGoalPosition).LengthSq() <= 0.01f)
        {
            mUp = true;
            mGoingUp = false;
            mOwner->SetPosition(mGoalPosition);
        }
    }
}

DoorComponent::DoorComponent(GameActor* pOwner, const float pZMovement, const float pInterpSpeed ):
    ActorComponent(pOwner, Transform::Origin),
    mGoalPosition(mOwner->GetWorldTransform().GetPosition() + Vector3(0.0f,0.0f,pZMovement)),
    mInterpSpeed(pInterpSpeed), mUp(false), mGoingUp(false)
{
}

void DoorComponent::Up()
{
    if (!mUp)
    {
        mGoingUp = true;
    }
}
