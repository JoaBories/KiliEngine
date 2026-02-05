#pragma once

#include "Window.h"
#include "SDL_render.h"
#include "SDL_image.h"
#include "Texture.h"
#include "GameActor.h"

#include "Struct.h"
using Struct::Rectangle2;
using Struct::Color;
using Struct::Transform2D;

class SpriteComponent;
class Scene;

class GameRenderer
{
private:
	SDL_Renderer* mSdlRenderer;
	std::vector<SpriteComponent*> mSpriteComponents;

public:
	GameRenderer() : mSdlRenderer(nullptr) {};
	GameRenderer(const GameRenderer&) = delete;
	GameRenderer& operator= (const GameRenderer&) = delete;

	bool Initialize(Window& rWindow);
	void BeginDraw();
	void EndDraw();
	void Close();

	void DrawRect(const Rectangle2& rRect, Color color = Color::WHITE) const;
	void DrawRectOutline(const Rectangle2& rRect, Color color = Color::WHITE) const;
	void DrawCircle(Vector2 pos, float radius, Color color = Color::WHITE) const;
	
	SDL_Renderer* GetSdlRenderer() const { return mSdlRenderer; };

	void DrawSprites();
	void DrawSprite(const GameActor& owner, const Texture& text, Transform2D pSpriteTransform, Rectangle2 size, Vector2 pivot, SDL_RendererFlip flip) const;
	void AddSprite(SpriteComponent* pSprite);
	void RemoveSprite(SpriteComponent* pSprite);
};