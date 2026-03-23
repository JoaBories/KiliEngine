#pragma once

#include "ActorComponent.h"

#include "Engine/Assets/Texture.h"
#include "Utils/Struct.h"

using Struct::Transform2D;
using Struct::Vector2;

class SpriteComponent : public ActorComponent
{
protected:
	Texture* mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
	bool mFlipX;

public:
	SpriteComponent(GameActor* pOwner, Transform pTransform, Texture* pTexture, int pDrawOrder = 100);
	~SpriteComponent() override;

	SpriteComponent() = delete;
	SpriteComponent(const SpriteComponent&) = delete;
	SpriteComponent& operator= (const SpriteComponent&) = delete;

	virtual void SetTexture(Texture* pTexture);
	virtual void Draw(GlRenderer* pRenderer);

	void SetFlipX(bool pFlipx) { mFlipX = pFlipx; }

	//Getters
	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexWidth() const { return mTexWidth; }
	int GetTexHeight() const { return mTexHeight; }

	// Inherited via ActorComponent
	void OnUpdate() override;
};

