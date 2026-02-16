#pragma once

#include "SDL_render.h"
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

	bool Initialize(Window& rWindow) override;
	void BeginDraw() override;
	void Draw() override;
	void EndDraw() override;
	void DrawSprites() override;
	void Close() override;

	void DrawSprite(GameActor* pActor, const Texture& pTex, Rectangle pSourceRect, Vector2 pOrigin, SDL_RendererFlip flip) const override;
	void AddSprite(SpriteComponent* pSprite) override;
	void RemoveSprite(SpriteComponent* pSprite) override;
	RendererType GetType() override;

	SDL_Renderer* GetSdlRenderer() const { return mSdlRenderer; };
};