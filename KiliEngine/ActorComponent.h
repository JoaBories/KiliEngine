#pragma once

class GameActor;

class ActorComponent
{
protected:
	bool mIsActive;
	short mUpdateOrder;
	GameActor& mOwner;

public:

	ActorComponent() = delete;

	inline ActorComponent(GameActor& owner, int updateOrder = 0) :
		mIsActive(true), mUpdateOrder(updateOrder),
		mOwner(owner)
	{
	}

	virtual ~ActorComponent() = 0;
	virtual void OnStart() = 0;
	virtual void Update() = 0;
	virtual void OnEnd() = 0;
};

