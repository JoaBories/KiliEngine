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
	mWorldTransform.RecomputeWorldTransformMatrix();
	return mWorldTransform;
}

void ActorComponent::UpdateWorldTransform()
{
	if (mWorldNeedUpdate)
	{
		mWorldNeedUpdate = false;
		Vector3 positionRotate = mLocalTransform.GetPosition().x * mLocalTransform.GetForwardVector() + mLocalTransform.GetPosition().y * mLocalTransform.GetUpVector() + mLocalTransform.GetPosition().z * mLocalTransform.GetRightVector();
		Vector3 positionScale = positionRotate * mOwner->GetTransform().GetScale();
		mWorldTransform.SetPosition(mOwner->GetTransform().GetPosition() + positionScale);
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
