#include "Player.h"
#include "Scene.h"
#include "GameRenderer.h"
#include "Utils.h"
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

	mTransform.position += mVelocity * Time::deltaTime;

	if (mTransform.position.x < 50.0f)
	{
		mTransform.position.x = 50.0f;
		mVelocity = Vector2::zero;
	}
	else if (mTransform.position.x > 750.0f)
	{
		mTransform.position.x = 750.0f;
		mVelocity = Vector2::zero;
	}

	if (!mInput)
	{
		mVelocity *= 0.95f;
	}
	mInput = false;

}

void Player::Render(const GameRenderer* renderer)
{
	mScene->GetRenderer()->DrawRect(Rectangle{ mTransform.position, Vector2(50, 50) * mTransform.scale, 0.0f });
}

void Player::OnInputMove(float side)
{
	mVelocity += Vector2::right * mAcceleration * side * Time::deltaTime * 1000.0f;
}
