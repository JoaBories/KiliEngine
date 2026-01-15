#pragma once
#include <string>
#include "Window.h"

class GameEngine
{
private:
	std::string mTitle;
	Window* mWindow;
	bool mIsRunning;

public:
	GameEngine(std::string Title);

	void Init();
	void Loop();
	void Render();
	void Update();
	void CheckForInputs();
	void Close();
};

