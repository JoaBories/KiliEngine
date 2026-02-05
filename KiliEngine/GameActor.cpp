#include "GameActor.h"
#include "ActorComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>
#include <vector>

GameActor::GameActor(Transform2D transform, ActorTags tag) :
	mScene(SceneManager::ActiveScene()), mActiveState(Active),
	mTransform(transform), mTag(tag),
	mComponents()
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

void GameActor::RemoveComponent(ActorComponent* comp)
{
	std::vector<ActorComponent*>::iterator it = std::find(mComponents.begin(), mComponents.end(), comp);

	while (it != mComponents.end()) 
	{
		mComponents.erase(it);
		it = std::find(mComponents.begin(), mComponents.end(), comp);
	}
}