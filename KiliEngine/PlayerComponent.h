#pragma once
#include "MoveComponent.h"

constexpr float PLAYER_ACCELERATION = 10.0f;
constexpr float PLAYER_DECCELERATION = 10.0f;
constexpr float PLAYER_VELOCITYPOWER = 1.0f;
constexpr float PLAYER_SPEED = 400.0f;
constexpr float PLAYER_GRAVITY = 750.0f;
constexpr float PLAYER_MAXYSPEED = 500.0f;
constexpr float PLAYER_JUMPFORCE = 450.0f;

class PlayerComponent : public MoveComponent
{

private :
	bool mIsGrounded;
	Vector2 mStartPos;

public :
	PlayerComponent(GameActor* pOwner, int pUpdateOrder);

	PlayerComponent() = delete;
	PlayerComponent(const PlayerComponent&) = delete;
	PlayerComponent& operator= (const PlayerComponent&) = delete;

	void Update() override;

	bool GetGrounded() const { return mIsGrounded; };
	void SetGrounded(bool grounded) { mIsGrounded = grounded; };
};

