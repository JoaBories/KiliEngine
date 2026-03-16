#pragma once

#include <SDL.h>
#include "Utils/Struct.h"
using Struct::Vector2;

class Window
{
private:
	SDL_Window* mSdlWindow;

public:

	Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	Vector2 GetDimensions() const;

	SDL_Window* GetSdlWindow() const { return mSdlWindow; }

	bool Open();
	void Close();
};

