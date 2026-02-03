#pragma once

#include "ActorComponent.h"
#include "GameRenderer.h"

#include "Struct.h"
using Struct::Transform2D;

class Scene;

enum ActorState
{
	Active,
	Paused,
	Dead
};

enum ActorTags
{
	ActorDefault,
	ActorBlock,
	ActorPlayer
};

class GameActor
{
protected:
	Scene* mScene;
	ActorState mActiveState;
	Transform2D mTransform;
	ActorTags mTag;
	

	std::vector<ActorComponent*> mComponents;

public:

	GameActor(Transform2D pTransform, ActorTags pTag = ActorDefault);
	~GameActor();

	GameActor(const GameActor&) = delete;
	GameActor& operator=(const GameActor&) = delete;

	virtual void Start() = 0;
	virtual void Update() = 0;
	
	Transform2D GetTransform() const			{ return mTransform; };
	void SetTransform(Transform2D pTransform)	{ mTransform = pTransform; };
	void SetPosition(Vector2 pPosition)			{ mTransform.position = pPosition; };
	void SetScale(Vector2 pScale)				{ mTransform.scale = pScale; };
	void SetRotation(float pRotation)			{ mTransform.rotation = pRotation; };

	void Destroy()								{ mActiveState = ActorState::Dead; };
	void SetActive(bool pNewActive)				{ mActiveState = pNewActive ? Active : Paused; };
	bool GetActive() const						{ return mActiveState == Active; };
	ActorState GetState() const					{ return mActiveState; };

	ActorTags GetTag() const					{ return mTag; };
	Scene* GetScene() const						{ return mScene; };

	void SetScene(Scene* pScene) {
		mScene = pScene;
	};

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

