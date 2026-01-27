#pragma once

#include "Window.h"
#include "SDL_render.h"
#include "SDL_image.h"
#include "Texture.h"
#include "GameActor.h"

#include "Struct.h"
using Struct::Rectangle;
using Struct::Color;
using Struct::Transform2D;

class SpriteComponent;

enum class Flip
{
	None = SDL_FLIP_NONE,
	Horizontal = SDL_FLIP_HORIZONTAL,
	Vertical = SDL_FLIP_VERTICAL
};

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

	void DrawRect(const Rectangle& rRect, Color color = Color::WHITE) const;
	SDL_Renderer* GetSdlRenderer() const { return mSdlRenderer; };

	void DrawSprites();
	void DrawSprite(const GameActor& owner, const Texture& text, Transform2D pSpriteTransform, Rectangle size, Vector2 pivot, Flip flip) const;
	void AddSprite(SpriteComponent* pSprite);
	void RemoveSprite(SpriteComponent* pSprite);

};