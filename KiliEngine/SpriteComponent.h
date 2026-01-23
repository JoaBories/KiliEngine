#pragma once

#include "ActorComponent.h"
#include "Texture.h"

class SpriteComponent : public ActorComponent
{
protected:
	Texture mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;

public:
	SpriteComponent(GameActor* pOwner, Texture& pTexture, int pDrawOrder = 100);
	virtual ~SpriteComponent();

	SpriteComponent() = delete;
	SpriteComponent(const SpriteComponent&) = delete;
	SpriteComponent& operator= (const SpriteComponent&) = delete;

	virtual void SetTexture(const Texture& pTexture);
	virtual void Draw(GameRenderer& pRenderer);

	//Getters
	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexWidth() const { return mTexWidth; }
	int GetTexHeight() const { return mTexHeight; }
};

