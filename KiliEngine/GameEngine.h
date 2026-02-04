#pragma once
#include <string>
#include "SceneManager.h"
#include "Window.h"
#include "GameRenderer.h"

class GameEngine
{
private:
	bool mIsRunning;
	std::string mTitle;
	Window* mWindow;
	GameRenderer* mRenderer;

public:
	GameEngine(std::string pTitle);

	void Init();
	void Loop();
	void Render();
	void Update();
	void CheckForInputs();
	void Close();
};

