#include "AnimatedSpriteComponent.h"

#include "Engine/GameActor.h"
#include "Engine/Tools/GameTime.h"
#include "Engine/Tools/Log.h"

AnimatedSpriteComponent::AnimatedSpriteComponent(GameActor* pOwner, Transform pTransform, const Animation& pAnim, int pDrawOrder) :
	SpriteComponent(pOwner, pTransform, pAnim.Textures[0], pDrawOrder), mCurrentFrame(0.0f),
	mPlaying(false), mLooping(false)
{
	SetName("AnimatedSpriteComponent");
	mAnimation = pAnim;
}

void AnimatedSpriteComponent::SetAnimation(const Animation& pAnimation)
{
	mAnimation = pAnimation;
	Reset();
}

void AnimatedSpriteComponent::SetAnimationFps(const float pFps)
{
	mAnimation.Fps = pFps;
}

void AnimatedSpriteComponent::OnUpdate()
{
	if (mAnimation.Textures.empty() || !mPlaying) return; // do nothing if there is no anim
	
	mCurrentFrame += mAnimation.Fps * GameTime::DeltaTime;
	
	const float size = static_cast<float>(mAnimation.Textures.size());
	if (mCurrentFrame >= size)
	{
		Reset();
		if (mLooping) Play(true);
	}

	SetTexture(mAnimation.Textures[static_cast<int>(mCurrentFrame)]); // change texture from sprite component
}

void AnimatedSpriteComponent::PlayAnimation(const Animation& pAnimation, bool pLoop)
{
	SetAnimation(pAnimation);
	Reset();
	mLooping = pLoop;
	mPlaying = true;
}

void AnimatedSpriteComponent::SetFrame(const int pFrame)
{
	if (static_cast<int>(mAnimation.Textures.size()) > pFrame)
	{
		SetTexture(mAnimation.Textures[pFrame]);
		mCurrentFrame = static_cast<float>(pFrame);
	}
}

void AnimatedSpriteComponent::SetLooping(const bool pLoop)
{
	mLooping = pLoop;
}

void AnimatedSpriteComponent::Play(const bool pLoop)
{
	mPlaying = true;
	mLooping = pLoop;
}

void AnimatedSpriteComponent::Pause()
{
	mPlaying = false;
}

void AnimatedSpriteComponent::Reset()
{
	mCurrentFrame = 0.0f;
	mPlaying = false;
	mLooping = false;
	SetTexture(mAnimation.Textures[0]);
}
