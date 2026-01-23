#pragma once

#include "GameActor.h"

class Alien :
	public GameActor
{
public :
	Alien(Transform2D transform) : GameActor(transform) {};

	// Inherited via GameActor
	void Start() override;
	void Update() override;
	void Render(const GameRenderer* renderer) override;
};

