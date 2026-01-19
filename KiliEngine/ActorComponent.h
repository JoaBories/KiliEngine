#pragma once

class GameActor;

class ActorComponent
{
protected:
	bool mIsActive;
	short mUpdateOrder;
	GameActor* mOwner;

public:

	ActorComponent() = delete;

	virtual ~ActorComponent() { OnEnd(); };

	ActorComponent(GameActor* owner, short updateOrder = 100) :
		mIsActive(true), mUpdateOrder(updateOrder),
		mOwner(owner)
	{
	}

	ActorComponent(const ActorComponent&) = delete;
	ActorComponent& operator=(const ActorComponent&) = delete;

	virtual void OnStart() {};
	virtual void Update() = 0;
	virtual void OnEnd() {};

	bool IsActive() const			{ return mIsActive; };
	void SetActive(bool newActive)	{ mIsActive = newActive; };

	short GetUpdateOrder() const	{ return mUpdateOrder; };
	GameActor* GetOwner() const		{ return mOwner; };
};

