#pragma once

#include "ActorComponent.h"
#include "Struct.h"

using Struct::Vector2;

class MoveComponent : public ActorComponent
{
protected:
	Vector2 mVelocity;
	float mVelocityDecay;
	float mMaxVelocity;
	bool mUpdated;

public:
	MoveComponent(GameActor* pOwner, float pMaxVelocity, float pVelocityDecay = 1.0f, int pUpdateOrder = 100);

	MoveComponent() = delete;
	MoveComponent(const MoveComponent&) = delete;
	MoveComponent& operator= (const MoveComponent&) = delete;

	Vector2 GetVelocity() const { return mVelocity; }
	void SetVelocity(Vector2 pVelocity);
	void AddVelocity(Vector2 pVelocity);

	void Update() override;
};

