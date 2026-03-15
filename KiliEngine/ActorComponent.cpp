#include "ActorComponent.h"
#include "GameActor.h"

void ActorComponent::Start() 
{
	OnStart();
}

void ActorComponent::End()
{
	OnEnd();
}

void ActorComponent::Update() 
{
	OnUpdate();
}

const WorldTransform& ActorComponent::GetWorldTransform()
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
		const WorldTransform ownerTransform = mOwner->GetWorldTransform();
		mWorldTransform.SetPosition(ownerTransform.GetWorldTransformMatrix().TransformVector3(mLocalTransform.GetPosition()));
		mWorldTransform.SetRotation(Quaternion::Concatenate(ownerTransform.GetRotation(), mLocalTransform.GetRotation()));
		mWorldTransform.SetScale(ownerTransform.GetScale() * mLocalTransform.GetScale());
	}
}

void ActorComponent::SetLocalTransform(const Transform& pTransform)
{
	mLocalTransform = pTransform;
	mWorldNeedUpdate = true;
}

void ActorComponent::SetLocalPosition(const Vector3& pPosition)
{
	mLocalTransform.SetPosition(pPosition);
	mWorldNeedUpdate = true;
}

void ActorComponent::SetLocalScale(const Vector3& pScale)
{
	mLocalTransform.SetScale(pScale);
	mWorldNeedUpdate = true;
}

void ActorComponent::SetLocalRotation(const Quaternion& pRotation)
{
	mLocalTransform.SetRotation(pRotation);
	mWorldNeedUpdate = true;
}