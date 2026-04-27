#pragma once

#include "SDL.h"
#include "SDL_keycode.h"
#include <vector>
#include "Utils/Struct.h"
using Struct::Vector2;

class Inputs
{
	static std::vector<SDL_Keycode> mCurrentPressedInputs;
	static std::vector<Uint8> mCurrentMouseInputs;
	static std::vector<Uint8> mButtonsDownThisFrame;
	static int mLastMouseDeltaX;
	static int mLastMouseDeltaY;
	static int mLastScrollY;

public:
	static bool mCapturingMouse;

	static void Init();
	static void Update();
	static bool InputUpdate(SDL_Event pEvent); // Return false if ExitKey

	static void SetMouseTracking(bool pIsTracking);
	
	static bool IsKeyPressed(SDL_Keycode pKey);
	static bool IsButtonPressed(Uint8 pButton, bool pThisFrame);
	static Vector2 GetMouseDelta();
	static int GetScrollY();
};

