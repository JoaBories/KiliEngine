#include "AnimatedComponent.h"

#include "Engine/GameActor.h"
#include "Engine/Tools/GameTime.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"

AnimatedComponent::AnimatedComponent(GameActor* pOwner, const Animation& pAnim) :
	ActorComponent(pOwner, Transform::Origin), mCurrentFrame(0.0f),
	mPlaying(false), mLooping(false)
{
	SetName("AnimatedComponent");
	mAnimation = pAnim;
}

void AnimatedComponent::SetAnimation(const Animation& pAnimation)
{
	mAnimation = pAnimation;
	Reset();
}

void AnimatedComponent::SetAnimationFps(const float pFps)
{
	mAnimation.Fps = pFps;
}

bool AnimatedComponent::SetTexture(Texture* pTexture) const
{
	bool ret = false;
	
	if (mSprite) 
	{
		mSprite->SetTexture(pTexture); // change texture from sprite component 
		ret = true;
	}
	if (mMesh)
	{
		mMesh->SetTextureOverride(pTexture); // change texture from mesh override
		ret = true;
	}
	
	return ret;
}

void AnimatedComponent::OnUpdate()
{
	if (mAnimation.Textures.empty() || !mPlaying) return; // do nothing if there is no anim
	
	mCurrentFrame += mAnimation.Fps * GameTime::DeltaTime;
	
	const float size = static_cast<float>(mAnimation.Textures.size());
	if (mCurrentFrame >= size)
	{
		Reset();
		if (mLooping) Play(true);
	}

	SetTexture(mAnimation.Textures[static_cast<int>(mCurrentFrame)]);
}

void AnimatedComponent::OnStart()
{
	mSprite = mOwner->GetComponent<SpriteComponent>();	
	mMesh = mOwner->GetComponent<MeshComponent>();
}

void AnimatedComponent::PlayAnimation(const Animation& pAnimation, const bool pLoop)
{
	SetAnimation(pAnimation);
	Reset();
	mLooping = pLoop;
	mPlaying = true;
}

void AnimatedComponent::SetFrame(const int pFrame)
{
	if (static_cast<int>(mAnimation.Textures.size()) > pFrame)
	{
		SetTexture(mAnimation.Textures[pFrame]);
		mCurrentFrame = static_cast<float>(pFrame);
	}
}

void AnimatedComponent::SetLooping(const bool pLoop)
{
	mLooping = pLoop;
}

void AnimatedComponent::Play(const bool pLoop)
{
	mPlaying = true;
	mLooping = pLoop;
}

void AnimatedComponent::Pause()
{
	mPlaying = false;
}

void AnimatedComponent::Reset()
{
	mCurrentFrame = 0.0f;
	mPlaying = false;
	mLooping = false;
	SetTexture(mAnimation.Textures[0]);
}
