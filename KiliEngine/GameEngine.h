#pragma once
#include <string>
#include "SceneManager.h"
#include "Window.h"
#include "SdlRenderer.h"
#include "OpenGlRenderer.h"

class GameEngine
{
private:
	bool mIsRunning;
	std::string mTitle;
	Window* mWindow;
	IRenderer* mRenderer;

public:
	GameEngine(std::string pTitle);

	void Init();
	void Loop();
	void Render();
	void Update();
	void CheckForInputs();
	void Close();
};

