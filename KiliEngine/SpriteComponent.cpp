#include "SpriteComponent.h"
#include "GameActor.h"
#include "SceneManager.h"
#include "Log.h"
#include "SDL_image.h"

SpriteComponent::SpriteComponent(GameActor* pOwner, Transform pTransform, Texture* pTexture, int pDrawOrder) :
	ActorComponent(pOwner, pTransform),
	mTexture(pTexture), mDrawOrder(pDrawOrder),
	mFlipX(false)
{
	mTexture->UpdateInfo(mTexWidth, mTexHeight);
	SceneManager::ActiveScene()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	SceneManager::ActiveScene()->GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::SetTexture(Texture* pTexture)
{
	mTexture = pTexture;
	mTexture->UpdateInfo(mTexWidth, mTexHeight);
}

void SpriteComponent::Draw(IRenderer* pRenderer)
{
	Vector2 origin{ mTexWidth / 2.0f, mTexHeight / 2.0f };
	pRenderer->DrawSprite(GetOwner(), GetWorldTransform(), *mTexture, Rectangle(), origin, (mFlipX) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void SpriteComponent::OnUpdate()
{
}
