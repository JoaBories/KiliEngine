#pragma once

#include "Window.h"

#include "Utils.h"
using Struct::Rectangle;

class GameRenderer
{
private:
	SDL_Renderer* mSdlRenderer;

public:
	GameRenderer() : mSdlRenderer(nullptr) {};
	GameRenderer(const GameRenderer&) = delete;
	GameRenderer& operator= (const GameRenderer&) = delete;

	bool Initialize(Window& rWindow);
	void BeginDraw();
	void EndDraw();
	void Close();

	void DrawRect(const Rectangle& rRect) const;

};

