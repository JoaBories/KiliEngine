#pragma once
#include "SpriteComponent.h"

class AnimatedSpriteComponent : public SpriteComponent
{
private:

	std::vector<Texture*> mAnimationTextures;
	float mCurrentFrame;
	float mAnimFps;

public:

	AnimatedSpriteComponent(GameActor* pOwner, Transform2D pTransform, const std::vector<Texture*>& pTexture, float pFps, int pDrawOrder = 100);
	virtual ~AnimatedSpriteComponent();

	AnimatedSpriteComponent() = delete;
	AnimatedSpriteComponent(const AnimatedSpriteComponent&) = delete;
	AnimatedSpriteComponent& operator=(const AnimatedSpriteComponent&) = delete;

	float GetAnimationFps() const { return mAnimFps; }
	void SetAnimationTextures(const std::vector<Texture*>& pTextures);
	void SetAnimationFps(float pFps);

	void Update() override;
};