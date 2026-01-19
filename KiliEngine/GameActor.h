#pragma once

#include "ActorComponent.h"

#include "Utils.h"
using Struct::Transform2D;

class Scene;

enum ActorState
{
	Active,
	Paused,
	Dead
};

class GameActor
{
protected:
	Scene& mScene;
	ActorState mState;
	Transform2D mTransform;
	std::vector<ActorComponent*> mComponents;

public:

	GameActor(Scene& scene, Transform2D transform) :
		mScene(scene), mState(Active),
		mTransform(transform),
		mComponents()
	{
	};

	Transform2D GetTransform() const { return mTransform; };

	void AddComponent(ActorComponent* comp) {
		mComponents.push_back(comp);
	};

	void RemoveComponent(ActorComponent* comp) {
		for (size_t i = 0; i < mComponents.size(); i++)
		{
			if (mComponents.at(i) == comp)
			{
				mComponents.erase(mComponents.begin() + i);
			}
		}
	};

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void SetActive(ActorState newState) = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;
};

