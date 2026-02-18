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
		WorldTransform ownerTransform = mOwner->GetTransform();
		mWorldTransform.SetPosition(ownerTransform.GetWorldTransformMatrix().TransformVector3(mLocalTransform.GetPosition()));
		mWorldTransform.SetRotation(Quaternion::Concatenate(ownerTransform.GetRotation(), mLocalTransform.GetRotation()));
		mWorldTransform.SetScale(ownerTransform.GetScale() * mLocalTransform.GetScale());
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

void ActorComponent::SetLocalRotation(Quaternion pRotation)
{
	mLocalTransform.SetRotation(pRotation);
	mWorldNeedUpdate = true;
}
