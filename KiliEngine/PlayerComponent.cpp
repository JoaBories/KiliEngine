#include "PlayerComponent.h"
#include "GameActor.h"
#include "Inputs.h"
#include "Time.h"
#include "Log.h"
#include "MathUtils.h"
#include "SceneManager.h"

PlayerComponent::PlayerComponent(GameActor* pOwner, int pUpdateOrder) :
	MoveComponent(pOwner, pUpdateOrder),
	mIsGrounded(true)
{
	mStartPos = mOwner->GetTransform().position;
}

void PlayerComponent::Update()
{
	MoveComponent::Update();
	
	if (Inputs::IsKeyPressed(SDLK_r))
	{
		SceneManager::ReloadScene();
	}

	// Movement X
	int side = 0;
	if (Inputs::IsKeyPressed(SDLK_RIGHT)) side = 1;
	else if (Inputs::IsKeyPressed(SDLK_LEFT)) side = -1;

	float targetSpeed = (side == 0) ? 0 : side * PLAYER_SPEED;
	float speedDiff = targetSpeed - mVelocity.x;
	float accelRate = (MathUtils::Abs(targetSpeed) > 0.01f) ? PLAYER_ACCELERATION : PLAYER_DECCELERATION;
	float movement = std::pow(MathUtils::Abs(speedDiff) * accelRate, PLAYER_VELOCITYPOWER) * MathUtils::Sign(speedDiff);

	AddVelocity(mOwner->GetTransform().Right() * movement * Time::deltaTime);

	// Gravity
	AddVelocity(mOwner->GetTransform().Up() * PLAYER_GRAVITY * Time::deltaTime);

	if (Inputs::IsKeyPressed(SDLK_SPACE) && mIsGrounded)
	{
		AddVelocity(-mOwner->GetTransform().Up() * PLAYER_JUMPFORCE);
		mIsGrounded = false;
	}

	mVelocity.y = MathUtils::Clamp(mVelocity.y, -PLAYER_MAXYSPEED, PLAYER_MAXYSPEED);

	if (mOwner->GetTransform().position.y >= 800)
	{
		mOwner->SetPosition(mStartPos);
	}
}
