#include "Player.h"
#include "Scene.h"
#include "GameRenderer.h"
#include "Struct.h"
#include "Time.h"
#include "Inputs.h"
#include "Bullet.h"
#include <vector>
#include "AssetManager.h"
#include "Log.h"

void Player::Start()
{
	std::vector<Texture*> anims;
	for (size_t i = 0; i < 22; i++)
	{
		anims.push_back(&AssetManager::GetTexture("run_" + std::to_string(i)));
	}

	mSprite = new AnimatedSpriteComponent(this, Transform2D::one, anims, 30.0f);
	AddComponent(mSprite);

	mBoxCollider = new BoxCollider2D(this, 10, Rectangle{ Vector2::zero, Vector2(50,50) });
	AddComponent(mBoxCollider);

	mMoveComp = new MoveComponent(this, 450.0f, 0.93f, 10);
	AddComponent(mMoveComp);
}

void Player::Update()
{
	for (ActorComponent* component : mComponents)
	{
		component->Update();
	}

	int side = 0;

	if (Inputs::IsKeyPressed(SDLK_RIGHT)) side = 1000;
	else if (Inputs::IsKeyPressed(SDLK_LEFT)) side = -1000;

	mMoveComp->AddVelocity(mTransform.Right() * mAcceleration * side * Time::deltaTime);

	if (Inputs::IsKeyPressed(SDLK_SPACE))
	{
		mScene->AddActor(new Bullet(mTransform.position, Vector2::down));
	}

	if (mTransform.position.x < 50.0f)
	{
		mTransform.position.x = 50.0f;
		mMoveComp->SetVelocity(Vector2::zero);
	}
	else if (mTransform.position.x > 750.0f)
	{
		mTransform.position.x = 750.0f;
		mMoveComp->SetVelocity(Vector2::zero);
	}

	if (mMoveComp->GetVelocity().x > 0)
	{
		mSprite->SetFlipX(false);
	}
	else
	{
		mSprite->SetFlipX(true);
	}
}