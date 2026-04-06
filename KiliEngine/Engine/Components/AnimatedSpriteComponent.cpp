#include "AnimatedSpriteComponent.h"

#include "Engine/GameActor.h"
#include "Engine/Tools/GameTime.h"
#include "Engine/Tools/Log.h"

AnimatedSpriteComponent::AnimatedSpriteComponent(GameActor* pOwner, Transform pTransform, const Animation& pAnim, int pDrawOrder) :
	SpriteComponent(pOwner, pTransform, pAnim.Textures[0], pDrawOrder), mCurrentFrame(0.0f)
{
	SetName("AnimatedSpriteComponent");
	mAnimation = pAnim;
}

void AnimatedSpriteComponent::SetAnimationTextures(const std::vector<Texture*>& pTextures)
{
	mAnimation.Textures = pTextures;
	if (!mAnimation.Textures.empty()) {
		SetTexture(mAnimation.Textures[0]);
	}
}

void AnimatedSpriteComponent::SetAnimationFps(const float pFps)
{
	mAnimation.Fps = pFps;
}

void AnimatedSpriteComponent::OnUpdate()
{
	if (mAnimation.Textures.empty()) return; // do nothing if there is no anim
	
	mCurrentFrame += mAnimation.Fps * GameTime::DeltaTime;
	
	const float size = static_cast<float>(mAnimation.Textures.size());
	while (mCurrentFrame >= size) // time modulo frame number
	{
		mCurrentFrame -= size;
	}

	SetTexture(mAnimation.Textures[static_cast<int>(mCurrentFrame)]); // change texture from sprite component
}