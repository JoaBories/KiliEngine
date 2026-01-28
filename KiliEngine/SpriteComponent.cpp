#include "SpriteComponent.h"
#include "GameActor.h"
#include "Scene.h"
#include "Log.h"
#include "SDL_image.h"

using Struct::Transform2D;

SpriteComponent::SpriteComponent(GameActor* pOwner, Transform2D pTransform, Texture& pTexture, int pDrawOrder) :
	ActorComponent(pOwner),
	mTexture(pTexture), mDrawOrder(pDrawOrder),
	mTransform(pTransform), mFlipX(false)
{
	mTexture.UpdateInfo(mTexWidth, mTexHeight);
	mOwner->GetScene()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetScene()->GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::SetTexture(const Texture& pTexture)
{
	mTexture = pTexture;
	mTexture.UpdateInfo(mTexWidth, mTexHeight);
}

void SpriteComponent::Draw(SdlRenderer& pRenderer)
{
	Vector2 origin{ mTexWidth / 2.0f, mTexHeight / 2.0f };
	pRenderer.DrawSprite(*mOwner, mTexture, mTransform, Rectangle(), origin, (mFlipX) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void SpriteComponent::Update()
{
}
