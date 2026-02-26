#include "GameEngine.h"
#include <iostream>

#include "AssetManager.h"
#include "Log.h"
#include "GameTime.h"
#include "Inputs.h"
#include "Config.h"
#include "PhysicManager.h"

GameEngine::GameEngine(const std::string& pTitle) :
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
	mWindow = new Window(WINDOW_WIDTH, WINDOW_HEIGHT);
	mRenderer = new GlRenderer();

	if (mWindow->Open()) 
	{
		if (mRenderer->Initialize(*mWindow))
		{
			AssetManager::Init(mRenderer);
			Inputs::Init();
			SceneManager::LoadScene(mRenderer);
			Loop();
		}
	}
}

void GameEngine::Loop()
{
	while (mIsRunning)
	{
		GameTime::ComputeDeltaTime();

		CheckForInputs();
		Update();

		Render();

		GameTime::DelayTime();
	}

	Log::Info(" Avg : " + std::to_string(1000.0f/GameTime::GetAvgFrameTime()));
	Close();
}

void GameEngine::Render()
{
	mRenderer->BeginDraw();

	mRenderer->Draw();

	mRenderer->EndDraw();
}

void GameEngine::Update()
{
	SceneManager::UpdateScene();
	PhysicManager::Update();
}

void GameEngine::CheckForInputs()
{
	if (mIsRunning)
	{
		Inputs::MouseUpdate();
		
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_QUIT:
				mIsRunning = false;
				break;

			default:
				if (Inputs::InputUpdate(event))
				{
					mIsRunning = false;
				}
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