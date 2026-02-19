#include "SdlRenderer.h"
#include "Log.h"
#include "Utils/Struct.h"
#include "Utils/MathUtils.h"
#include "SpriteComponent.h"
#include "OpenGlRenderer.h"

using namespace MathUtils;

bool SdlRenderer::Initialize(Window& rWindow)
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

void SdlRenderer::BeginDraw()
{
	SDL_SetRenderDrawColor(mSdlRenderer, 120, 120, 255, 255);
	SDL_RenderClear(mSdlRenderer);
}

void SdlRenderer::EndDraw()
{
	SDL_RenderPresent(mSdlRenderer);
}

void SdlRenderer::Draw()
{
}

void SdlRenderer::Close()
{
	SDL_DestroyRenderer(mSdlRenderer);
}

void SdlRenderer::DrawSprites()
{
	for (SpriteComponent* sc : mSpriteComponents)
	{
		sc->Draw(this);
	}
}

void SdlRenderer::AddSprite(SpriteComponent* pSprite)
{
	int spriteDrawOrder = pSprite->GetDrawOrder();
	std::vector<SpriteComponent*>::iterator sc;
	for (sc = mSpriteComponents.begin(); sc != mSpriteComponents.end(); ++sc)
	{
		if (spriteDrawOrder < (*sc)->GetDrawOrder()) break;
	}
	mSpriteComponents.insert(sc, pSprite);
}

void SdlRenderer::RemoveSprite(SpriteComponent* pSprite)
{
	std::vector<SpriteComponent*>::iterator sc;
	sc = std::find(mSpriteComponents.begin(), mSpriteComponents.end(), pSprite);
	mSpriteComponents.erase(sc);
}

void SdlRenderer::DrawSprite(GameActor* pActor, WorldTransform pTransform, const Texture& pTex, Rectangle pSourceRect, Vector2 pOrigin, SDL_RendererFlip flip) const
{
	SDL_Rect destinationRect;
	destinationRect.w = static_cast<int>(pTex.GetWidth() * pTransform.GetScale().x);
	destinationRect.h = static_cast<int>(pTex.GetHeight() * pTransform.GetScale().y);
	destinationRect.x = static_cast<int>(pTransform.GetPosition().x - pOrigin.x);
	destinationRect.y = static_cast<int>(pTransform.GetPosition().y - pOrigin.y);

	SDL_Rect* sourceSDL = nullptr;
	if (pSourceRect != Rectangle::Null)
	{
		sourceSDL = new SDL_Rect{ pSourceRect.toSdlRect() };
	}

	SDL_RenderCopyEx(mSdlRenderer,
		pTex.GetTexture(),
		sourceSDL,
		&destinationRect,
		-pTransform.GetRotation().z,
		nullptr,
		flip);

	delete sourceSDL;
}

RendererType SdlRenderer::GetType()
{
	return Sdl;
}

