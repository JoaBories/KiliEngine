#pragma once

#include "IRenderer.h"

class OpenGlRenderer : public IRenderer
{
	// Inherited via IRenderer
	bool Initialize(Window& pWindow) override;
	void Close() override;
	void BeginDraw() override;
	void EndDraw() override;
	void Draw() override;
	void DrawSprites() override;
	RendererType GetType() override;
	void DrawSprite(GameActor* pActor, const Texture& pTex, Rectangle pSourceRect, Vector2 pOrigin, SDL_RendererFlip flip) const override;
};

