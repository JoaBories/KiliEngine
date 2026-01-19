#pragma once

#include "GameActor.h"

class Alien :
	public GameActor
{
public :
	Alien(Scene* scene, Transform2D transform) : GameActor(scene, transform) {};

	// Inherited via GameActor
	void Start() override;
	void Update() override;
	void Render(const GameRenderer* renderer) override;
};

