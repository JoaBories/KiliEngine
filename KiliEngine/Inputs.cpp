#include "Inputs.h"

std::vector<SDL_Keycode> Inputs::mCurrentPressedInputs = {};

void Inputs::InputUpdate(SDL_Event event)
{
	if (event.type == SDL_KEYUP)
	{
		std::vector<SDL_Keycode>::iterator it = std::find(mCurrentPressedInputs.begin(), mCurrentPressedInputs.end(), event.key.keysym.sym);
		if (it != mCurrentPressedInputs.end())
		{
			mCurrentPressedInputs.erase(it);
		}
	}
	else if (event.type == SDL_KEYDOWN)
	{
		std::vector<SDL_Keycode>::iterator it = std::find(mCurrentPressedInputs.begin(), mCurrentPressedInputs.end(), event.key.keysym.sym);
		if (it == mCurrentPressedInputs.end())
		{
			mCurrentPressedInputs.emplace_back(event.key.keysym.sym);
		}
	}    
}

bool Inputs::IsKeyPressed(SDL_Keycode key)
{
	std::vector<SDL_Keycode>::iterator it = std::find(mCurrentPressedInputs.begin(), mCurrentPressedInputs.end(), key);
	if (it != mCurrentPressedInputs.end())
	{
		return true;
	}

	return false;
}
