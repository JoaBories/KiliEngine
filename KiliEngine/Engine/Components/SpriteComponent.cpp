#include "SpriteComponent.h"
#include "Engine/GameActor.h"
#include "Engine/Scene/SceneManager.h"
#include "Engine/Tools/Log.h"
#include "Engine/Renderer/OpenGlRenderer.h"

SpriteComponent::SpriteComponent(GameActor* pOwner, const Transform& pTransform, Texture* pTexture, const int pDrawOrder) :
	ActorComponent(pOwner, pTransform),
	mTexture(pTexture), mDrawOrder(pDrawOrder),
	mFlipX(false)
{
	SetName("SpriteComponent");
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

void SpriteComponent::Draw(GlRenderer* pRenderer)
{
	Vector2 origin{ mTexWidth / 2.0f, mTexHeight / 2.0f };
	pRenderer->DrawSprite(GetOwner(), GetWorldTransform(), *mTexture, Rectangle(), origin, mFlipX ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void SpriteComponent::OnUpdate()
{
}
