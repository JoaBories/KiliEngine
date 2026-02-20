#pragma once

#include "ActorComponent.h"

#include "Utils/Struct.h"
using Struct::Transform2D;
using Struct::Vector2;
#include "Transform.h"

class Scene;

enum ActorState : Uint8
{
	WaitingStart,
	Active,
	Paused,
	Dead
};

enum ActorTags : Uint8
{
	ActorDefault,
	ActorBlock,
	ActorPlayer
};

class GameActor
{
private:
	ActorState mActiveState;
	WorldTransform mTransform;
	ActorTags mTag;
	std::vector<ActorComponent*> mComponents;

protected:
	// only called by the base class in Start() and Update()
	virtual void OnStart() {}
	virtual void OnEarlyUpdate() {} // Before components
	virtual void OnLateUpdate() {}  // After components

	void UpdateComponentsTransform();

public:
	GameActor(const Transform& pTransform, ActorTags pTag = ActorDefault);
	~GameActor();

	GameActor(const GameActor&) = delete;
	GameActor& operator=(const GameActor&) = delete;

	void Start();
	void Update();

	const WorldTransform& GetWorldTransform() const;
	void SetTransform(WorldTransform pTransform);
	void AddPosition(Vector3 pPosition);
	void SetPosition(Vector3 pPosition);
	void SetScale(Vector3 pScale);
	void AddRotation(Quaternion pRotation);
	void SetRotation(Quaternion pRotation);

	void Destroy()							{ mActiveState = Dead; }
	void SetActive(const bool pNewActive)	{ mActiveState = pNewActive ? Active : Paused; }
	bool GetActive() const					{ return mActiveState == Active; }
	ActorState GetState() const				{ return mActiveState; }

	ActorTags GetTag() const				{ return mTag; }

	void RemoveComponent(ActorComponent* pComp) ;

	void AddComponent(ActorComponent* pComp) {
		if (mActiveState != WaitingStart) pComp->Start();
		mComponents.push_back(pComp);
	}

	template<typename T> T* GetComponent() const
	{
		for (ActorComponent* c : mComponents)
			if (T* comp = dynamic_cast<T*>(c)) return comp;
		return nullptr;
	}

	template<typename T> std::vector<T*> GetComponents() const
	{
		std::vector<T*> comps = {};
		for (ActorComponent* c : mComponents)
			if (T* comp = dynamic_cast<T*>(c)) comps.push_back(comp);
		return comps;
	}
};

