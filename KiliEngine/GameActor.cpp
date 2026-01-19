#include "GameActor.h"

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

template<typename T>
T* GameActor::GetComponent() const
{
	for (ActorComponent* c : mComponents)
		if (T* comp = dynamic_cast<T*>(c)) return comp;
	return nullptr;
}

template<typename T>
std::vector<T*> GameActor::GetComponents() const
{
	std::vector<T*> comps = {};
	for (ActorComponent* c : mComponents)
		if (T* comp = dynamic_cast<T*>(c)) comps.push_back(comp);
	return comps;
}
