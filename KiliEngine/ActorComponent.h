#pragma once

class GameActor;

class ActorComponent
{
protected:
	bool mIsActive;
	short mUpdateOrder;
	GameActor* mOwner;
	Transform mTransform; // relative transform from owner

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

	void Start();
	void Update();

	virtual void OnStart() {};
	virtual void Update() = 0;
	virtual void OnEnd() {};

	Transform GetTransform() { return mTransform; };
	void SetTransform(Transform pTransform) { mTransform = pTransform; };
	void SetPosition(Vector3 pPosition) { mTransform.SetPosition(pPosition); };
	void SetScale(Vector3 pScale) { mTransform.SetScale(pScale); };
	void SetRotation(Vector3 pRotation) { mTransform.SetRotation(pRotation); };

	bool IsActive() const			{ return mIsActive; };
	void SetActive(bool newActive)	{ mIsActive = newActive; };

	short GetUpdateOrder() const	{ return mUpdateOrder; };
	GameActor* GetOwner() const		{ return mOwner; };
};

