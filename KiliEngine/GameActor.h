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
	ActorTags mTag;
	std::vector<ActorComponent*> mComponents;

protected:
	
	WorldTransform mTransform;
	
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
	void SetTransform(const WorldTransform& pTransform);
	void AddPosition(const Vector3& pPosition);
	void SetPosition(const Vector3& pPosition);
	void SetScale(const Vector3& pScale);
	void AddRotation(const Quaternion& pRotation);
	void Rotate(const Vector3& pAxis, float pAngle);
	void SetRotation(const Quaternion& pRotation);

	void Destroy()							{ mActiveState = Dead; }
	void SetActive(const bool pNewActive)	{ mActiveState = pNewActive ? Active : Paused; }
	bool GetActive() const					{ return mActiveState == Active; }
	ActorState GetState() const				{ return mActiveState; }

	ActorTags GetTag() const				{ return mTag; }

	void RemoveComponent(const ActorComponent* pComp) ;

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

