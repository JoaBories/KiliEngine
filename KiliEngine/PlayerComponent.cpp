#include "PlayerComponent.h"
#include "GameActor.h"
#include "Inputs.h"
#include "Time.h"
#include "Log.h"

PlayerComponent::PlayerComponent(GameActor* pOwner, int pUpdateOrder) :
	MoveComponent(pOwner, PLAYER_MAXSPEED, PLAYER_VELDECAY, pUpdateOrder)
{
}

void PlayerComponent::Update()
{
	MoveComponent::Update();

	int side = 0;

	if (Inputs::IsKeyPressed(SDLK_RIGHT)) side = PLAYER_ACCELERATION;
	else if (Inputs::IsKeyPressed(SDLK_LEFT)) side = -PLAYER_ACCELERATION;

	if (side != 0) AddVelocity(mOwner->GetTransform().Right() * side * Time::deltaTime);
	
	Log::Info(mVelocity.toString());
}
