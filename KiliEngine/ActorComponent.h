#pragma once

#include <utility>

#include "Transform.h"

class GameActor;

class ActorComponent
{
private:
	bool mIsActive;
	bool mWorldNeedUpdate;
	short mUpdateOrder;
	GameActor* mOwner;
	Transform mLocalTransform;
	WorldTransform mWorldTransform;

protected:
	virtual void OnStart() {}
	virtual void OnUpdate() = 0;
	virtual void OnEnd() {}

public:
	ActorComponent() = delete;
	virtual ~ActorComponent() { ActorComponent::OnEnd(); }

	ActorComponent(GameActor* pOwner, Transform pTransform, const short pUpdateOrder = 100) :
		mIsActive(true), mWorldNeedUpdate(true),
		mUpdateOrder(pUpdateOrder),
		mOwner(pOwner), mLocalTransform(std::move(pTransform))
	{
	}

	ActorComponent(const ActorComponent&) = delete;
	ActorComponent& operator=(const ActorComponent&) = delete;

	void Start();
	void Update();

	Transform GetLocalTransform() const { return mLocalTransform; }
	WorldTransform GetWorldTransform();
	void UpdateWorldTransform();
	void UpdatedOwnerTransform() { mWorldNeedUpdate = true; }
	void SetLocalTransform(const Transform& pTransform);
	void SetLocalPosition(const Vector3& pPosition);
	void SetLocalScale(const Vector3& pScale);
	void SetLocalRotation(const Quaternion& pRotation);

	bool IsActive() const			{ return mIsActive; }
	void SetActive(const bool pNewActive)	{ mIsActive = pNewActive; }

	short GetUpdateOrder() const	{ return mUpdateOrder; }
	GameActor* GetOwner() const		{ return mOwner; }
};

