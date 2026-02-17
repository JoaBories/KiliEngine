#pragma once
#include "GameActor.h"
#include "SpriteComponent.h"

class TestActor : public GameActor
{
public:
	TestActor(Transform transform) :
		GameActor(transform)
	{
	}
};