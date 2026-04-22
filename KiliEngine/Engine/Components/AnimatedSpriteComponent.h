#pragma once
#include "SpriteComponent.h"

class AnimatedSpriteComponent : public SpriteComponent
{
private:
	Animation mAnimation;
	float mCurrentFrame;
	bool mPlaying;
	bool mLooping;

public:
	AnimatedSpriteComponent(GameActor* pOwner, Transform pTransform, const Animation& pAnim, int pDrawOrder = 100);
	~AnimatedSpriteComponent() override = default;

	AnimatedSpriteComponent() = delete;
	AnimatedSpriteComponent(const AnimatedSpriteComponent&) = delete;
	AnimatedSpriteComponent& operator=(const AnimatedSpriteComponent&) = delete;

	float GetAnimationFps() const { return mAnimation.Fps; }
	
	void SetAnimation(const Animation& pAnimation);
	void SetAnimationFps(float pFps);

	void OnUpdate() override;

	void PlayAnimation(const Animation& pAnimation, bool pLoop);
	void SetFrame(int pFrame);
	void SetLooping(bool pLoop);
	void Play(bool pLoop);
	void Pause();
	void Reset();
};