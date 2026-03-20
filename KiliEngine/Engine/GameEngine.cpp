#include "GameEngine.h"
#include <iostream>

#include "Assets/AssetManager.h"
#include "Tools/Log.h"
#include "Tools/GameTime.h"
#include "Tools/Inputs.h"
#include "Config.h"
#include "PhysicManager.h"

#ifdef _DEBUG
#include "Gui.h"
#endif

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
	mWindow = new Window();
	mRenderer = new GlRenderer();

	if (mWindow->Open()) 
	{
		if (mRenderer->Initialize(*mWindow))
		{
			GameTime::Init();
#ifdef _DEBUG
			Gui::Init(mWindow, mRenderer);
#endif
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
#ifdef _DEBUG
	Gui::BeginGui();
#endif

	mRenderer->Draw();
	
#ifdef _DEBUG
	Gui::EndGui();
#endif
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
#ifdef _DEBUG
				Gui::Input(event);
#endif
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

#ifdef _DEBUG
	Gui::Close();	
#endif

	mWindow->Close();
	delete mWindow;
	mWindow = nullptr;

	mRenderer->Close();
	delete mRenderer;
	mWindow = nullptr;

	//_CrtDumpMemoryLeaks();
}