#pragma once

#include "Window.h"
#include "SDL_image.h"
#include "Transform.h"
#include "MeshComponent.h"
#include "Camera.h"

#include "Utils/Struct.h"
using Struct::Rectangle;

class Texture;
class SpriteComponent;

enum RendererType : Uint8
{
	Sdl,
	OpenGl,
};

class IRenderer
{
protected:
	Camera* mCamera = nullptr;
	
public:
	virtual ~IRenderer() = default;

	virtual bool Initialize(Window& pWindow) = 0;
	virtual void Close() = 0;
	virtual void BeginDraw() = 0;
	virtual void EndDraw() = 0;
	virtual void Draw() = 0;
	virtual RendererType GetType() = 0;

	void SetCamera(Camera* pCamera) { mCamera = pCamera; }
	
	virtual void DrawSprite(GameActor* pActor, WorldTransform pTransform, const Texture& pTex, Rectangle pSourceRect, Vector2 pOrigin, SDL_RendererFlip pFlip) const {}
	virtual void AddSprite(SpriteComponent* pSprite) {}
	virtual void RemoveSprite(SpriteComponent* pSprite) {}

	virtual void AddMesh(MeshComponent* pMesh) {}
	virtual void RemoveMesh(const MeshComponent* pMesh) {}
};