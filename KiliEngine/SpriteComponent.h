#pragma once

#include "ActorComponent.h"
#include "Texture.h"
#include "Struct.h"

using Struct::Transform2D;
using Struct::Vector2;

class SpriteComponent : public ActorComponent
{
protected:
	Transform2D mTransform;
	Texture mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
	bool mFlipX;

public:
	SpriteComponent(GameActor* pOwner, Transform2D pTransform, Texture& pTexture, int pDrawOrder = 100);
	virtual ~SpriteComponent();

	SpriteComponent() = delete;
	SpriteComponent(const SpriteComponent&) = delete;
	SpriteComponent& operator= (const SpriteComponent&) = delete;

	virtual void SetTexture(const Texture& pTexture);
	virtual void Draw(SdlRenderer& pRenderer);

	void SetFlipX(bool pFlipx) { mFlipX = pFlipx; };

	//Getters
	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexWidth() const { return mTexWidth; }
	int GetTexHeight() const { return mTexHeight; }

	// Inherited via ActorComponent
	void Update() override;
};

