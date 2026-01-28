#pragma once

#include "IRenderer.h"

#include "SDL_render.h"
#include "SDL_image.h"
#include "GameActor.h"

class GameActor;
class SpriteComponent;

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
	void Close() override;
	void BeginDraw() override;
	void EndDraw() override;
	void Draw() override;
	void DrawSprites() override;
	void RendererType GetType() override

	void DrawRect(const Rectangle& rRect, Color color = Color::WHITE) const;
	SDL_Renderer* GetSdlRenderer() const { return mSdlRenderer; };

	void DrawSprite(const GameActor& owner, const Texture& text, Transform2D pSpriteTransform, Rectangle size, Vector2 pivot, SDL_RendererFlip flip) const;
	void AddSprite(SpriteComponent* pSprite);
	void RemoveSprite(SpriteComponent* pSprite);

	// Inherited via IRenderer
	RendererType GetType() override;
};