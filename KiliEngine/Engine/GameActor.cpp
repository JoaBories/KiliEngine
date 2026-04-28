#include "GameActor.h"
#include "Components/ActorComponent.h"
#include "Scene/Scene.h"
#include <algorithm>
#include <vector>

#include "Tools/Log.h"

void GameActor::UpdateComponentsTransform()
{
	for (ActorComponent* component : mComponents)
	{
		component->UpdatedOwnerTransform();
	}
}

GameActor::GameActor(const Transform& pTransform, const std::string& pName, const ActorTags pTag) :
	mActiveState(ActorState::WaitingStart), mTag(pTag), mName(pName), mTransform(pTransform)
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
	mActiveState = ActorState::Active;

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