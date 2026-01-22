#pragma once

#include "ActorComponent.h"
#include "GameRenderer.h"

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
	Scene* mScene;
	ActorState mActiveState;
	Transform2D mTransform;

	std::vector<ActorComponent*> mComponents;

public:

	GameActor(Scene* scene, Transform2D transform) :
		mScene(scene), mActiveState(Active),
		mTransform(transform),
		mComponents()
	{
	};

	virtual ~GameActor();

	GameActor(const GameActor&) = delete;
	GameActor& operator=(const GameActor&) = delete;

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render(const GameRenderer* renderer) = 0;
	
	Transform2D GetTransform() const	{ return mTransform; };

	void Destroy()						{ mActiveState = ActorState::Dead; };
	void SetActive(bool newActive)		{ mActiveState = newActive ? Active : Paused; };
	bool GetActive() const				{ return mActiveState == Active; };
	ActorState GetState() const			{ return mActiveState; };

	void RemoveComponent(ActorComponent* comp) ;

	void AddComponent(ActorComponent* comp) {
		mComponents.push_back(comp);
	};

	template<typename T> T* GetComponent() const
	{
		for (ActorComponent* c : mComponents)
			if (T* comp = dynamic_cast<T*>(c)) return comp;
		return nullptr;
	};

	template<typename T> std::vector<T*> GetComponents() const
	{
		std::vector<T*> comps = {};
		for (ActorComponent* c : mComponents)
			if (T* comp = dynamic_cast<T*>(c)) comps.push_back(comp);
		return comps;
	};

};

