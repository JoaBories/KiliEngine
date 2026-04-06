#pragma once
#include "SpriteComponent.h"

class AnimatedSpriteComponent : public SpriteComponent
{
private:
	Animation mAnimation;
	float mCurrentFrame;

public:
	AnimatedSpriteComponent(GameActor* pOwner, Transform pTransform, const Animation& pAnim, int pDrawOrder = 100);
	~AnimatedSpriteComponent() override = default;

	AnimatedSpriteComponent() = delete;
	AnimatedSpriteComponent(const AnimatedSpriteComponent&) = delete;
	AnimatedSpriteComponent& operator=(const AnimatedSpriteComponent&) = delete;

	float GetAnimationFps() const { return mAnimation.Fps; }
	
	void SetAnimation(const Animation& pAnimation) { mAnimation = pAnimation; }
	
	void SetAnimationTextures(const std::vector<Texture*>& pTextures);
	void SetAnimationFps(float pFps);

	void OnUpdate() override;
};