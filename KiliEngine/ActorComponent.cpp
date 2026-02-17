#include "ActorComponent.h"
#include "GameActor.h"


void ActorComponent::Start() 
{
	OnStart();
}

void ActorComponent::Update() 
{
	OnUpdate();
}

WorldTransform ActorComponent::GetWorldTransform()
{
	UpdateWorldTransform();
	return mWorldTransform;
}

void ActorComponent::UpdateWorldTransform()
{
	if (mWorldNeedUpdate)
	{
		mWorldNeedUpdate = false;
		mWorldTransform.SetPosition(mOwner->GetTransform().GetPosition() + mLocalTransform.GetPosition());
		mWorldTransform.SetRotation(mOwner->GetTransform().GetRotation() + mLocalTransform.GetRotation());
		mWorldTransform.SetScale(mOwner->GetTransform().GetScale() * mLocalTransform.GetScale());
	}
}

void ActorComponent::SetLocalTransform(Transform pTransform)
{
	mLocalTransform = pTransform;
	mWorldNeedUpdate = true;
}

void ActorComponent::SetLocalPosition(Vector3 pPosition)
{
	mLocalTransform.SetPosition(pPosition);
	mWorldNeedUpdate = true;
}

void ActorComponent::SetLocalScale(Vector3 pScale)
{
	mLocalTransform.SetScale(pScale);
	mWorldNeedUpdate = true;
}

void ActorComponent::SetLocalRotation(Vector3 pRotation)
{
	mLocalTransform.SetRotation(pRotation);
	mWorldNeedUpdate = true;
}
