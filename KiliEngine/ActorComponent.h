#pragma once

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
	virtual void OnStart() {};
	virtual void OnUpdate() = 0;
	virtual void OnEnd() {};

public:
	ActorComponent() = delete;
	virtual ~ActorComponent() { OnEnd(); };

	ActorComponent(GameActor* owner, Transform transform, short updateOrder = 100) :
		mIsActive(true), mUpdateOrder(updateOrder),
		mOwner(owner),
		mLocalTransform(transform), mWorldNeedUpdate(true)
	{
	}

	ActorComponent(const ActorComponent&) = delete;
	ActorComponent& operator=(const ActorComponent&) = delete;

	void Start();
	void Update();

	Transform GetLocalTransform() const { return mLocalTransform; };
	WorldTransform GetWorldTransform();
	void UpdateWorldTransform();
	void UpdatedOwnerTransform() { mWorldNeedUpdate = true; };
	void SetLocalTransform(Transform pTransform);
	void SetLocalPosition(Vector3 pPosition);
	void SetLocalScale(Vector3 pScale);
	void SetLocalRotation(Vector3 pRotation);

	bool IsActive() const			{ return mIsActive; };
	void SetActive(bool newActive)	{ mIsActive = newActive; };

	short GetUpdateOrder() const	{ return mUpdateOrder; };
	GameActor* GetOwner() const		{ return mOwner; };
};

