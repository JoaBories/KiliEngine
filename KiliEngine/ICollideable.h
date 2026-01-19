#pragma once

#include "Utils.h"
using Struct::Vector2;

class GameActor;

class ICollideable
{
public:

	virtual void Collide(GameActor& other, Vector2 overlap) = 0;
};

