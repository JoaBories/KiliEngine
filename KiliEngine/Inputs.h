#pragma once

#include "SDL.h"
#include "SDL_keycode.h"
#include <vector>
#include "Struct.h"
using Struct::Vector2;

constexpr SDL_Keycode ExitKey = SDLK_ESCAPE; //todo move it to a config file

class Inputs
{
	static std::vector<SDL_Keycode> mCurrentPressedInputs;
	static int mLastMouseDeltaX;
	static int mLastMouseDeltaY;

public:

	static void Init();
	static void MouseUpdate();
	static bool InputUpdate(SDL_Event pEvent); // Return false if ExitKey
	
	static bool IsKeyPressed(SDL_Keycode pKey);
	static Vector2 GetMouseDelta();
};

