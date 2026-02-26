#pragma once

#include "ActorComponent.h"
#include "Vector3.h"

class MoveComponent : public ActorComponent
{
protected:
	Vector3 mVelocity;

public:
	explicit MoveComponent(GameActor* pOwner, short pUpdateOrder = 100);

	MoveComponent() = delete;
	MoveComponent(const MoveComponent&) = delete;
	MoveComponent& operator= (const MoveComponent&) = delete;

	Vector3 GetVelocity() const { return mVelocity; }
	void SetVelocity(const Vector3& pVelocity);
	void AddVelocity(const Vector3& pVelocity);

	void OnUpdate() override;
};

