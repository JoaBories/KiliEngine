#pragma once

#include "ActorComponent.h"
#include "Vector3.h"

class MoveComponent : public ActorComponent
{
protected:
	Vector3 mVelocity;

public:
	MoveComponent(GameActor* pOwner, Transform pTransform, int pUpdateOrder = 100);

	MoveComponent() = delete;
	MoveComponent(const MoveComponent&) = delete;
	MoveComponent& operator= (const MoveComponent&) = delete;

	Vector3 GetVelocity() const { return mVelocity; }
	void SetVelocity(Vector3 pVelocity);
	void AddVelocity(Vector3 pVelocity);

	void OnUpdate() override;
};

