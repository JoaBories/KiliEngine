#include "GameRenderer.h"
#include "Log.h"

GameRenderer::GameRenderer() : mSdlRenderer(nullptr)
{
}

bool GameRenderer::Initialize(Window& rWindow)
{
	mSdlRenderer = SDL_CreateRenderer(rWindow.GetSdlWindow(), -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!mSdlRenderer)
	{
		Log::Error(LogType::Video, "Failed to create Renderer");
		return false;
	}
	return true;
}

void GameRenderer::BeginDraw()
{
	SDL_SetRenderDrawColor(mSdlRenderer, 120, 120, 255, 255);
	SDL_RenderClear(mSdlRenderer);
}

void GameRenderer::EndDraw()
{
	SDL_RenderPresent(mSdlRenderer);
}

void GameRenderer::Close()
{
	SDL_DestroyRenderer(mSdlRenderer);
}

void GameRenderer::DrawRect(Rectangle& rRect)
{
	SDL_SetRenderDrawColor(mSdlRenderer, 255, 255, 255, 255);
	SDL_Rect sdlRect = rRect.toSdlRect();
	SDL_RenderFillRect(mSdlRenderer, &sdlRect);
}

