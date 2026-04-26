#pragma once
#include "ActorComponent.h"
#include "Engine/Assets/Texture.h"

class SpriteComponent;
class MeshComponent;

class AnimatedComponent : public ActorComponent
{
private:
	SpriteComponent* mSprite;
	MeshComponent* mMesh;
	Animation mAnimation;
	float mCurrentFrame;
	bool mPlaying;
	bool mLooping;
	
	bool SetTexture(Texture* pTexture) const;
	
protected:
	void OnUpdate() override;
	void OnStart() override;

public:
	AnimatedComponent(GameActor* pOwner, const Animation& pAnim);
	~AnimatedComponent() override = default;

	AnimatedComponent() = delete;
	AnimatedComponent(const AnimatedComponent&) = delete;
	AnimatedComponent& operator=(const AnimatedComponent&) = delete;

	float GetAnimationFps() const { return mAnimation.Fps; }
	
	void SetAnimation(const Animation& pAnimation);
	void SetAnimationFps(float pFps);

	void PlayAnimation(const Animation& pAnimation, bool pLoop);
	void SetFrame(int pFrame);
	void SetLooping(bool pLoop);
	void Play(bool pLoop);
	void Pause();
	void Reset();
};
