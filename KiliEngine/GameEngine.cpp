#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine(std::string title) : mIsRunning(true), mTitle(title), mWindow(nullptr)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	}
	else
	{
		std::cout << "SDL initialization succeeded!";
	}

	Init();
}

void GameEngine::Init()
{
	mWindow = new Window(800, 800);
	if (mWindow->Open()) Loop();
}

void GameEngine::Loop()
{
	while (mIsRunning)
	{
		CheckForInputs();
		Update();
		Render();
	}

	Close();
}

void GameEngine::Render()
{
}

void GameEngine::Update()
{
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
				//send inputs
				break;
			}
		}
	}
}

void GameEngine::Close() 
{
	mWindow->Close();
}
