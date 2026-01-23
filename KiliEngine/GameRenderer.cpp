#include "GameRenderer.h"
#include "Log.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "Struct.h"
#include "Window.h"
#include "SpriteComponent.h"
#include "MathUtils.h"

using namespace MathUtils;

bool GameRenderer::Initialize(Window& rWindow)
{
	mSdlRenderer = SDL_CreateRenderer(rWindow.GetSdlWindow(), -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!mSdlRenderer)
	{
		Log::Error(LogType::Video, "Failed to create Renderer");
		return false;
	}
	else
	{
		Log::Info("Created Renderer Successfully");
	}

	const int flags = IMG_INIT_PNG;
	const int initted = IMG_Init(flags);
	if ((initted & flags) != flags)
	{
		std::string ErrorMsg = std::string("Unable to initialize SDL_Image") + IMG_GetError();
		Log::Error(LogType::Video, "Unable to initialize SDL_Image" + ErrorMsg);
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

void GameRenderer::DrawRect(const Rectangle& rRect, Color color) const
{
	SDL_SetRenderDrawColor(mSdlRenderer, 255, 255, 255, 255);
	SDL_Rect sdlRect = rRect.toSdlRect();
	SDL_RenderFillRect(mSdlRenderer, &sdlRect);
}

void GameRenderer::DrawSprites()
{
	for (SpriteComponent* sc : mSpriteComponents)
	{
		sc->Draw(*this);
	}
}

void GameRenderer::DrawSprite(const GameActor& pActor, const Texture& pTex, Rectangle pSourceRect, Vector2 pOrigin, Flip flip) const
{
	SDL_Rect destinationRect;
	Transform2D transform = pActor.GetTransform();
	destinationRect.w = static_cast<int>(pTex.GetWidth() * transform.scale.x);
	destinationRect.h = static_cast<int>(pTex.GetHeight() * transform.scale.y);
	destinationRect.x = static_cast<int>(transform.position.x - pOrigin.x);
	destinationRect.y = static_cast<int>(transform.position.y - pOrigin.y);

	SDL_Rect* sourceSDL = nullptr;
	if (pSourceRect != Rectangle::Null)
	{
		sourceSDL = new SDL_Rect{ pSourceRect.toSdlRect() };
	}

	SDL_RenderCopyEx(mSdlRenderer,
		pTex.GetTexture(),
		sourceSDL,
		&destinationRect,
		-transform.rotation,
		nullptr,
		SDL_FLIP_NONE);

	delete sourceSDL;
}

void GameRenderer::AddSprite(SpriteComponent* pSprite)
{
}

void GameRenderer::RemoveSprite(SpriteComponent* pSprite)
{
}

