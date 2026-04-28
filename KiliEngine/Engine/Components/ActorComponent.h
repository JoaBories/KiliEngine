#pragma once

#include "Engine/Transform.h"
#include "Engine/Transform.h"

class GameActor;

class ActorComponent
{
private:
	bool mIsActive;
	short mUpdateOrder;
	bool mWorldNeedUpdate;
	WorldTransform mWorldTransform;
	std::string mName;

protected:
	Transform mLocalTransform;
	GameActor* mOwner;
	
	virtual void OnStart() {}
	virtual void OnUpdate() = 0;
	virtual void OnEnd() {}

public:
	ActorComponent() = delete;
	virtual ~ActorComponent() = default;

	ActorComponent(GameActor* pOwner, const Transform& pTransform, const short pUpdateOrder = 100) :
		mIsActive(true), mUpdateOrder(pUpdateOrder),
		mWorldNeedUpdate(true),
		mName("ActorComponent"), mLocalTransform(pTransform), mOwner(pOwner)
	{
	}

	ActorComponent(const ActorComponent&) = delete;
	ActorComponent& operator=(const ActorComponent&) = delete;

	void Start();
	void End();
	void Update();

	const Transform& GetLocalTransform() const { return mLocalTransform; }
	const WorldTransform& GetWorldTransform();
	void UpdateWorldTransform();
	void UpdatedOwnerTransform() { mWorldNeedUpdate = true; }
	void SetLocalTransform(const Transform& pTransform);
	void SetLocalPosition(const Vector3& pPosition);
	void SetLocalScale(const Vector3& pScale);
	void SetLocalRotation(const Quaternion& pRotation);

	[[nodiscard]] bool IsActive() const			{ return mIsActive; }
	void SetActive(const bool pNewActive)	{ mIsActive = pNewActive; }

	short GetUpdateOrder() const	{ return mUpdateOrder; }
	GameActor* GetOwner() const		{ return mOwner; }

	std::string GetName() const		{ return mName; }
	void SetName(const std::string& pName)	{ mName = pName; }
};

