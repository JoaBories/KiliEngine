#pragma once
#include <string>
#include "Scene.h"
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
	std::vector<Scene*> mScenes;
	int mCurrentScene;

public:
	GameEngine(std::string pTitle, std::vector<Scene*> pScenes);

	void Init();
	void Loop();
	void Render();
	void Update();
	void CheckForInputs();
	void Close();
};

