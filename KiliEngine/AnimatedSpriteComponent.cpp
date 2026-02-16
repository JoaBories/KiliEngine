#include "AnimatedSpriteComponent.h"

#include "Time.h"
#include "Log.h"

AnimatedSpriteComponent::AnimatedSpriteComponent(GameActor* pOwner, Transform2D pTransform, const std::vector<Texture*>& pTexture, float pFps, int pDrawOrder) :
	SpriteComponent(pOwner, pTransform, pTexture[0], pDrawOrder), mCurrentFrame(0.0f), mAnimFps(pFps)
{
	SetAnimationTextures(pTexture);
}

AnimatedSpriteComponent::~AnimatedSpriteComponent()
{
}

void AnimatedSpriteComponent::SetAnimationTextures(const std::vector<Texture*>& pTextures)
{
	mAnimationTextures = pTextures;
	if (mAnimationTextures.size() > 0) {
		SetTexture(mAnimationTextures[0]);
	}
}

void AnimatedSpriteComponent::SetAnimationFps(float pFps)
{
	mAnimFps = pFps;
}

void AnimatedSpriteComponent::Update()
{
	SpriteComponent::Update();

	if (mAnimationTextures.size() == 0) return; // do nothing if there is no anim

	mCurrentFrame += mAnimFps * Time::deltaTime;
	while (mCurrentFrame >= mAnimationTextures.size()) // time modulo frame number
	{
		mCurrentFrame -= mAnimationTextures.size();
	}

	SetTexture(mAnimationTextures[static_cast<int>(mCurrentFrame)]); // change texture from sprite component
}