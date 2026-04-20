#include "Inputs.h"
#include "Engine/Config.h"
#include "Engine/Renderer/OpenGlRenderer.h"

std::vector<SDL_Keycode> Inputs::mCurrentPressedInputs = {};
std::vector<Uint8> Inputs::mCurrentMouseInputs = {};
std::vector<Uint8> Inputs::mButtonsDownThisFrame = {};
int Inputs::mLastMouseDeltaX = 0;
int Inputs::mLastMouseDeltaY = 0;
bool Inputs::mCapturingMouse = false;

void Inputs::Init()
{
	SetMouseTracking(Cfg::MOUSECAPTURE_DEFAULT);
	mCapturingMouse = Cfg::MOUSECAPTURE_DEFAULT;
}

void Inputs::Update()
{
	mButtonsDownThisFrame.clear();
	
	if (mCapturingMouse)
	{
		SDL_GetRelativeMouseState(&mLastMouseDeltaX, &mLastMouseDeltaY);
	}
}

bool Inputs::InputUpdate(SDL_Event pEvent)
{
	if (pEvent.type == SDL_KEYUP)
	{
		const auto it = std::find(mCurrentPressedInputs.begin(), mCurrentPressedInputs.end(), pEvent.key.keysym.sym);
		if (it != mCurrentPressedInputs.end())
		{
			mCurrentPressedInputs.erase(it);
		}
	}
	else if (pEvent.type == SDL_KEYDOWN)
	{
#ifdef _DEBUG
		if (pEvent.key.keysym.sym == Cfg::EXIT_KEY)
		{
			return true;
		}

		if (pEvent.key.keysym.sym == Cfg::MOUSECAPTURE_TOGGLE)
		{
			if (mCapturingMouse)
			{
				SetMouseTracking(false);
				mCapturingMouse = false;
				mLastMouseDeltaX = 0;
				mLastMouseDeltaY = 0;
			}
			else
			{
				SetMouseTracking(true);
				mCapturingMouse = true;
			}
		}
		
		if (pEvent.key.keysym.sym == Cfg::RENDER_MODE_DEFAULT) GlRenderer::RenderMode = DefaultRender;
		else if (pEvent.key.keysym.sym == Cfg::RENDER_MODE_UV) GlRenderer::RenderMode = Uvs;
		else if (pEvent.key.keysym.sym == Cfg::RENDER_MODE_NORMAL) GlRenderer::RenderMode = Normals;
		else if (pEvent.key.keysym.sym == Cfg::RENDER_MODE_WIREFRAME) GlRenderer::RenderMode = Wireframe;
#endif		
		const auto it = std::find(mCurrentPressedInputs.begin(), mCurrentPressedInputs.end(), pEvent.key.keysym.sym);
		if (it == mCurrentPressedInputs.end())
		{
			mCurrentPressedInputs.emplace_back(pEvent.key.keysym.sym);
		}
	}
	else if (pEvent.type == SDL_MOUSEBUTTONUP)
	{
		const auto it = std::find(mCurrentMouseInputs.begin(), mCurrentMouseInputs.end(), pEvent.button.button);
		if (it != mCurrentMouseInputs.end())
		{
			mCurrentMouseInputs.erase(it);
		}
	}
	else if (pEvent.type == SDL_MOUSEBUTTONDOWN)
	{
		const auto it = std::find(mCurrentMouseInputs.begin(), mCurrentMouseInputs.end(), pEvent.button.button);
		if (it == mCurrentMouseInputs.end())
		{
			mCurrentMouseInputs.emplace_back(pEvent.button.button);
		}
		
		mButtonsDownThisFrame.push_back(pEvent.button.button);
	}

	return false;
}

void Inputs::SetMouseTracking(const bool pIsTracking)
{
	SDL_SetRelativeMouseMode(pIsTracking ? SDL_TRUE : SDL_FALSE);
}

bool Inputs::IsKeyPressed(const SDL_Keycode pKey)
{
	const auto it = std::find(mCurrentPressedInputs.begin(), mCurrentPressedInputs.end(), pKey);
	if (it != mCurrentPressedInputs.end())
	{
		return true;
	}

	return false;
}

bool Inputs::IsButtonPressed(const Uint8 pButton, const bool pThisFrame)
{
	if (pThisFrame)
	{
		const auto it = std::find(mButtonsDownThisFrame.begin(), mButtonsDownThisFrame.end(), pButton);
		if (it != mButtonsDownThisFrame.end())
		{
			return true;
		}
		
		return false;
	}
	
	const auto it = std::find(mCurrentMouseInputs.begin(), mCurrentMouseInputs.end(), pButton);
	if (it != mCurrentMouseInputs.end())
	{
		return true;
	}

	return false;
}

Vector2 Inputs::GetMouseDelta()
{
	return {mLastMouseDeltaX, mLastMouseDeltaY};
}
