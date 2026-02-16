#pragma once
#include "GameActor.h"
#include "SpriteComponent.h"

class TestActor : public GameActor
{
public:
	TestActor(Transform2D transform) :
		GameActor(transform)
	{
	}

	void Start() override;
	void Update() override;
};

