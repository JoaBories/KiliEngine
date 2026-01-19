#pragma once
#include "SDL.h"

class IInput
{
public:
	virtual void OnInput(SDL_Event input) = 0;
};

