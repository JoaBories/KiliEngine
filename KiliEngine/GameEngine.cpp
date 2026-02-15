#include "GameEngine.h"
#include <iostream>
#include "Log.h"
#include "Time.h"
#include "Inputs.h"

GameEngine::GameEngine(std::string pTitle) :
	mIsRunning(true), mTitle(pTitle), 
	mWindow(nullptr), 
	mRenderer(nullptr)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		Log::Error(LogType::System, "SDL initialization failed. SDL Error: ");
	}
	else
	{
		Log::Info("SDL initialized successfully");
	}
}

void GameEngine::Init()
{
	mWindow = new Window(800, 800);
	mRenderer = new SdlRenderer();

	if (mWindow->Open()) 
	{
		if (mRenderer->Initialize(*mWindow))
		{
			SceneManager::LoadScene(mRenderer);

			Loop();
		}
	}
}

void GameEngine::Loop()
{
	while (mIsRunning)
	{
		Time::ComputeDeltaTime();

		CheckForInputs();
		Update();

		Render();

		Time::DelayTime();
	}

	Close();
}

void GameEngine::Render()
{
	mRenderer->BeginDraw();

	mRenderer->DrawSprites();

	mRenderer->EndDraw();
}

void GameEngine::Update()
{
	SceneManager::UpdateScene();
}

void GameEngine::CheckForInputs()
{
	if (mIsRunning)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_QUIT:
				mIsRunning = false;
				break;

			default:
				Inputs::InputUpdate(event);
				break;
			}
		}
	}
}

void GameEngine::Close() 
{
	Log::Info("Close Game");

	SceneManager::UnloadScene();

	mWindow->Close();
	delete mWindow;
	mWindow = nullptr;

	mRenderer->Close();
	delete mRenderer;
	mWindow = nullptr;

	//_CrtDumpMemoryLeaks();
}