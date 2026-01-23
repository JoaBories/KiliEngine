#pragma once

#include "SDL.h"
#include "SDL_keycode.h"
#include <vector>

class Inputs
{
	static std::vector<SDL_Keycode> mCurrentPressedInputs;

public:

	static void InputUpdate(SDL_Event event);
	static bool IsKeyPressed(SDL_Keycode key);
};

