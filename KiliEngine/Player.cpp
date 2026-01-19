#include "Player.h"
#include "BoxCollider2D.h"
#include "Log.h"
#include "Scene.h"
#include "Time.h"

void Player::Start()
{
	AddComponent(new BoxCollider2D(*this, 0, Rectangle{ Vector2::zero, Vector2(50,50) }));
}

void Player::SetActive(ActorState newState)
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

void Player::Render()
{
	mScene.GetRenderer()->DrawRect(Rectangle{ mTransform.position, Vector2(50, 50) * mTransform.scale, 0.0f });
}

void Player::Destroy()
{
}

void Player::Collide(GameActor& other, Vector2 overlap)
{
	Log::Info("HasCollided");
}

void Player::OnInput(SDL_Event input)
{
	switch (input.key.keysym.sym)
	{
	case SDLK_RIGHT:
		mVelocity += Vector2::right * mAcceleration * Time::deltaTime;
		mInput = true;

	case SDLK_LEFT:
		mVelocity += Vector2::left * mAcceleration * Time::deltaTime;
		mInput = true;
	}
}
