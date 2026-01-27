#include "SpriteComponent.h"
#include "GameActor.h"
#include "Scene.h"

using Struct::Transform2D;

SpriteComponent::SpriteComponent(GameActor* pOwner, Texture& pTexture, Transform2D pTransform, int pDrawOrder) :
	ActorComponent(pOwner),
	mTexture(pTexture), mDrawOrder(pDrawOrder),
	mTransform(pTransform)
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

void SpriteComponent::Draw(GameRenderer& pRenderer)
{
	Vector2 origin{ mTexWidth / 2.0f, mTexHeight / 2.0f };
	pRenderer.DrawSprite(*mOwner, mTexture, mTransform, Rectangle(), origin, Flip::None);
}

void SpriteComponent::Update()
{
}
