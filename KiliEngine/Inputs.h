#pragma once

#include "SDL.h"
#include "SDL_keycode.h"
#include <vector>
#include "Struct.h"
using Struct::Vector2;

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

