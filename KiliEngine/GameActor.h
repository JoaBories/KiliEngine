#pragma once

#include "ActorComponent.h"

#include "Utils/Struct.h"
using Struct::Transform2D;
using Struct::Vector2;
#include "Transform.h"

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
	ActorPlayer,
	ActorCoin
};

class GameActor
{
protected:
	ActorState mActiveState;
	Transform mTransform;
	ActorTags mTag;
	std::vector<ActorComponent*> mComponents;

	// only called by the base class in Start() and Update()
	virtual void OnStart() {};
	virtual void OnEarlyUpdate() {}; // Before components
	virtual void OnLateUpdate() {};  // After components

public:

	GameActor(Transform pTransform, ActorTags pTag = ActorDefault);
	~GameActor();

	GameActor(const GameActor&) = delete;
	GameActor& operator=(const GameActor&) = delete;

	void Start();
	void Update();
	
	Transform GetTransform()					{ return mTransform; };
	void SetTransform(Transform pTransform)		{ mTransform = pTransform; };
	void SetPosition(Vector3 pPosition)			{ mTransform.SetPosition(pPosition); };
	void SetScale(Vector3 pScale)				{ mTransform.SetScale(pScale); };
	void SetRotation(Vector3 pRotation)			{ mTransform.SetRotation(pRotation); };

	void Destroy()								{ mActiveState = ActorState::Dead; };
	void SetActive(bool pNewActive)				{ mActiveState = pNewActive ? Active : Paused; };
	bool GetActive() const						{ return mActiveState == Active; };
	ActorState GetState() const					{ return mActiveState; };

	ActorTags GetTag() const					{ return mTag; };

	void RemoveComponent(ActorComponent* comp) ;

	void AddComponent(ActorComponent* comp) {
		mComponents.push_back(comp);
		comp->OnStart();
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

