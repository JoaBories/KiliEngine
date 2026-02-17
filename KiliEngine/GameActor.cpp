#include "GameActor.h"
#include "ActorComponent.h"
#include "SceneManager.h"
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

GameActor::GameActor(WorldTransform transform, ActorTags tag) :
	mActiveState(WaitingStart), mTransform(transform), mTag(tag)
{
};

GameActor::~GameActor()
{
	for (ActorComponent* component : mComponents)
	{
		if (component)
		{
			delete component;
		}
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

void GameActor::SetTransform(WorldTransform pTransform)
{
	mTransform = pTransform;
	UpdateComponentsTransform();
}

void GameActor::AddPosition(Vector3 pPosition)
{
	mTransform.AddPosition(pPosition);
	UpdateComponentsTransform();
}

void GameActor::SetPosition(Vector3 pPosition)
{
	mTransform.SetPosition(pPosition);
	UpdateComponentsTransform();
}

void GameActor::SetScale(Vector3 pScale)
{
	mTransform.SetScale(pScale);
	UpdateComponentsTransform();
}

void GameActor::SetRotation(Vector3 pRotation)
{
	mTransform.SetRotation(pRotation);
	UpdateComponentsTransform();
}

void GameActor::RemoveComponent(ActorComponent* comp)
{
	std::vector<ActorComponent*>::iterator it = std::find(mComponents.begin(), mComponents.end(), comp);

	while (it != mComponents.end()) 
	{
		mComponents.erase(it);
		it = std::find(mComponents.begin(), mComponents.end(), comp);
	}
}