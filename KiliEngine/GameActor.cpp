#include "GameActor.h"
#include "ActorComponent.h"
#include "Scene.h"
#include <algorithm>
#include <vector>

void GameActor::UpdateComponentsTransform()
{
	for (ActorComponent* component : mComponents)
	{
		component->UpdatedOwnerTransform();
	}
}

GameActor::GameActor(const Transform& pTransform, const ActorTags pTag) :
	mActiveState(WaitingStart), mTransform(pTransform), mTag(pTag)
{
};

GameActor::~GameActor()
{
	for (ActorComponent* component : mComponents)
	{
		if (component) component->End();
		delete component;
	}

	mComponents.clear();
}

void GameActor::Start()
{
	mActiveState = Active;

	for (ActorComponent* component : mComponents)
	{
		component->Start();
	}

	OnStart();
}

void GameActor::Update()
{
	OnEarlyUpdate();

	for (ActorComponent* component : mComponents)
	{
		component->Update();
	}

	OnLateUpdate();
}

const WorldTransform& GameActor::GetWorldTransform() const
{
	mTransform.RecomputeWorldTransformMatrix();
	return mTransform;
}

void GameActor::SetTransform(const WorldTransform& pTransform)
{
	mTransform = pTransform;
	UpdateComponentsTransform();
}

void GameActor::AddPosition(const Vector3& pPosition)
{
	mTransform.AddPosition(pPosition);
	UpdateComponentsTransform();
}

void GameActor::SetPosition(const Vector3& pPosition)
{
	mTransform.SetPosition(pPosition);
	UpdateComponentsTransform();
}

void GameActor::SetScale(const Vector3& pScale)
{
	mTransform.SetScale(pScale);
	UpdateComponentsTransform();
}

void GameActor::AddRotation(const Quaternion& pRotation)
{
	mTransform.AddRotation(pRotation);
	UpdateComponentsTransform();
}

void GameActor::Rotate(const Vector3& pAxis, const float pAngle)
{
	mTransform.Rotate(pAxis, pAngle);
	UpdateComponentsTransform();
}

void GameActor::SetRotation(const Quaternion& pRotation)
{
	mTransform.SetRotation(pRotation);
	UpdateComponentsTransform();
}

void GameActor::RemoveComponent(const ActorComponent* pComp)
{
	std::vector<ActorComponent*>::iterator it = std::find(mComponents.begin(), mComponents.end(), pComp);

	while (it != mComponents.end()) 
	{
		mComponents.erase(it);
		it = std::find(mComponents.begin(), mComponents.end(), pComp);
	}
}