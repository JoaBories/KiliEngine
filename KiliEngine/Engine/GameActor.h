#pragma once

#include "Components/ActorComponent.h"

#include "Utils/Struct.h"
using Struct::Transform2D;
using Struct::Vector2;
#include "Transform.h"

class Scene;

enum class ActorState : Uint8
{
	WaitingStart,
	Active,
	Paused,
	Dead
};

enum class ActorTags : Uint8
{
	Default,
	Block,
	Player,
	Hud
};

class GameActor
{
private:
	ActorState mActiveState;
	ActorTags mTag;
	std::vector<ActorComponent*> mComponents;
	std::string mName;
	WorldTransform mTransform;

protected:
	
	// only called by the base class in Start() and Update()
	virtual void OnStart() {}
	virtual void OnEarlyUpdate() {} // Before components
	virtual void OnLateUpdate() {}  // After components

	void UpdateComponentsTransform();

public:
	explicit GameActor(const Transform& pTransform, const std::string& pName, ActorTags pTag = ActorTags::Default);
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

	void Destroy()							{ mActiveState = ActorState::Dead; }
	void SetActive(const bool pNewActive)	{ mActiveState = pNewActive ? ActorState::Active : ActorState::Paused; }
	bool GetActive() const					{ return mActiveState == ActorState::Active; }
	ActorState GetState() const				{ return mActiveState; }

	ActorTags GetTag() const				{ return mTag; }

	std::string GetName() const				{ return mName; }

	void RemoveComponent(const ActorComponent* pComp) ;

	void AddComponent(ActorComponent* pComp) {
		if (mActiveState != ActorState::WaitingStart) pComp->Start();
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

