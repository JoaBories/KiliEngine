#pragma once

#include "Window.h"
#include "GameActor.h"

#include "Utils/Struct.h"
using Struct::Rectangle;
using Struct::Transform2D;

class Texture;
class SpriteComponent;

enum RendererType
{
	SDL,
	OpenGL,
};

class IRenderer
{

public:

	virtual ~IRenderer() = default;

	virtual bool Initialize(Window& pWindow) = 0;
	virtual void Close() = 0;
	virtual void BeginDraw() = 0;
	virtual void EndDraw() = 0;
	virtual void Draw() = 0;
	virtual void DrawSprites() = 0;
	virtual RendererType GetType() = 0;
	virtual void DrawSprite(GameActor* pActor, const Texture& pTex, Rectangle pSourceRect, Vector2 pOrigin, SDL_RendererFlip flip) const = 0;
	virtual void AddSprite(SpriteComponent* pSprite) = 0;
	virtual void RemoveSprite(SpriteComponent* pSprite) = 0;
};

