#pragma once

#include <SDL.h>
#include "Utils.h"
using Struct::Vector2;

class Window
{
private:
	SDL_Window* mSdlWindow;
	Vector2 mDimensions;

public:

	Window(int pWidth, int pHeight);
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	inline Vector2 GetDimensions() const { return mDimensions; };

	inline SDL_Window* GetSdlWindow() const { return mSdlWindow; };

	bool Open();
	void Close();
};

