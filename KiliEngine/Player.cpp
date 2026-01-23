#include "Player.h"
#include "Scene.h"
#include "GameRenderer.h"
#include "Struct.h"
#include "Time.h"
#include "Inputs.h"
#include "Bullet.h"
#include "BoxCollider2D.h"

void Player::Start()
{
	AddComponent(new BoxCollider2D(this, 10, Rectangle{ Vector2::zero, Vector2(50,50) }));
}

void Player::Update()
{
	for (const auto& component : mComponents)
	{
		component->Update();
	}


	int side = 0;

	if (Inputs::IsKeyPressed(SDLK_RIGHT)) side = 1;
	else if (Inputs::IsKeyPressed(SDLK_LEFT)) side = -1;

	mVelocity += Vector2::right * mAcceleration * side * Time::deltaTime * 1000.0f;

	if (Inputs::IsKeyPressed(SDLK_SPACE))
	{
		mScene->AddActor(new Bullet(mTransform.position, Vector2::down));
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
	renderer->DrawRect(Rectangle{ mTransform.position, Vector2(50, 50) * mTransform.scale, 0.0f });
}
