#pragma once
#include <string>
#include "Window.h"
#include "Renderer/OpenGlRenderer.h"

class GameEngine
{
private:
	bool mIsRunning;
	std::string mTitle;
	Window* mWindow;
	GlRenderer* mRenderer;

public:
	GameEngine(const std::string& pTitle);

	void Init();
	void Loop();
	void Render();
	void Update();
	void CheckForInputs();
	void Close();
};

