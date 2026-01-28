#pragma once
#include "MoveComponent.h"

constexpr float PLAYER_ACCELERATION = 750.0f;
constexpr float PLAYER_MAXSPEED = 300.0f;
constexpr float PLAYER_VELDECAY = 0.92f;

class PlayerComponent : public MoveComponent
{

private :

public :
	PlayerComponent(GameActor* pOwner, int pUpdateOrder);

	PlayerComponent() = delete;
	PlayerComponent(const PlayerComponent&) = delete;
	PlayerComponent& operator= (const PlayerComponent&) = delete;

	void Update() override;
};

