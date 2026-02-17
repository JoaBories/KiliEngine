#pragma once
#include "GameActor.h"
#include "SpriteComponent.h"

class TestActor : public GameActor
{
protected:
	void OnEarlyUpdate() override;

public:
	TestActor(Transform transform) :
		GameActor(transform)
	{
	}

};