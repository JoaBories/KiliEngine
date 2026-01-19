#include "Player.h"
#include "BoxCollider2D.h"
#include "Log.h"
#include "Scene.h"
#include "Time.h"

void Player::Start()
{

}

void Player::Update()
{
	for (const auto& component : mComponents)
	{
		component->Update();
	}

	mVelocity = mVelocity.clamp(0, mMaxSpeed);
	mTransform.position += mVelocity * Time::deltaTime;
	mTransform.position = mTransform.position.clamp(0, 800);

	if (!mInput)
	{
		mVelocity *= 0.9f;
	}
	mInput = false;

}

void Player::Render(const GameRenderer* renderer)
{
	mScene->GetRenderer()->DrawRect(Rectangle{ mTransform.position, Vector2(50, 50) * mTransform.scale, 0.0f });
}