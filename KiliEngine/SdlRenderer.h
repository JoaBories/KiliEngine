#pragma once

#include "SDL_render.h"
#include "SDL_image.h"
#include "IRenderer.h"

class SdlRenderer : public IRenderer
{
private:
	SDL_Renderer* mSdlRenderer;
	std::vector<SpriteComponent*> mSpriteComponents;

public:
	SdlRenderer() : mSdlRenderer(nullptr) {};

	SdlRenderer(const SdlRenderer&) = delete;
	SdlRenderer& operator= (const SdlRenderer&) = delete;

	// Inherited via IRenderer
	bool Initialize(Window& rWindow) override;
	void Close() override;
	void BeginDraw() override;
	void EndDraw() override;
	void Draw() override;
	void DrawSprites() override;
	RendererType GetType() override;
	void DrawSprite(GameActor* pActor, const Texture& pTex, Rectangle pSourceRect, Vector2 pOrigin, SDL_RendererFlip flip) const override;

	SDL_Renderer* GetSdlRenderer() const { return mSdlRenderer; };

	void AddSprite(SpriteComponent* pSprite) override;
	void RemoveSprite(SpriteComponent* pSprite) override;

};