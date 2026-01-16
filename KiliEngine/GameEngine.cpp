#include "GameEngine.h"
#include <iostream>
#include "Log.h"
#include "Time.h"

GameEngine::GameEngine(std::string pTitle, std::vector<Scene*> pScenes) :
	mIsRunning(true), mTitle(pTitle), 
	mWindow(nullptr), 
	mRenderer(nullptr),
	mScenes(pScenes), mCurrentScene(0)
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
	mRenderer = new GameRenderer();

	if (mWindow->Open()) 
	{
		if (mRenderer->Initialize(*mWindow))
		{
			if (!mScenes.empty())
			{
				mScenes[0]->SetRenderer(mRenderer);
				mScenes[0]->Start();
			}

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

	mScenes[mCurrentScene]->Render();

	mRenderer->EndDraw();
}

void GameEngine::Update()
{
	mScenes[mCurrentScene]->Update();
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
				mScenes[mCurrentScene]->OnInput(event);
				break;
			}
		}
	}
}

void GameEngine::Close() 
{
	Log::Info("Close Game");

	mWindow->Close();
	delete mWindow;
	mWindow = nullptr;

	mRenderer->Close();
	delete mRenderer;
	mWindow = nullptr;
}
