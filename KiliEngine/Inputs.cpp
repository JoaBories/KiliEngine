#include "Inputs.h"
#include "Config.h"

std::vector<SDL_Keycode> Inputs::mCurrentPressedInputs = {};
int Inputs::mLastMouseDeltaX = 0;
int Inputs::mLastMouseDeltaY = 0;

void Inputs::Init()
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

void Inputs::MouseUpdate()
{
	SDL_GetRelativeMouseState(&mLastMouseDeltaX, &mLastMouseDeltaY);
}

bool Inputs::InputUpdate(SDL_Event pEvent)
{
	if (pEvent.type == SDL_KEYUP)
	{
		const std::vector<SDL_Keycode>::iterator it = std::find(mCurrentPressedInputs.begin(), mCurrentPressedInputs.end(), pEvent.key.keysym.sym);
		if (it != mCurrentPressedInputs.end())
		{
			mCurrentPressedInputs.erase(it);
		}
	}
	else if (pEvent.type == SDL_KEYDOWN)
	{
		if (pEvent.key.keysym.sym == EXIT_KEY)
		{
			return true;
		}
		
		const std::vector<SDL_Keycode>::iterator it = std::find(mCurrentPressedInputs.begin(), mCurrentPressedInputs.end(), pEvent.key.keysym.sym);
		if (it == mCurrentPressedInputs.end())
		{
			mCurrentPressedInputs.emplace_back(pEvent.key.keysym.sym);
		}
	}

	return false;
}

bool Inputs::IsKeyPressed(const SDL_Keycode pKey)
{
	const std::vector<SDL_Keycode>::iterator it = std::find(mCurrentPressedInputs.begin(), mCurrentPressedInputs.end(), pKey);
	if (it != mCurrentPressedInputs.end())
	{
		return true;
	}

	return false;
}

Vector2 Inputs::GetMouseDelta()
{
	return Vector2(mLastMouseDeltaX, mLastMouseDeltaY);
}
