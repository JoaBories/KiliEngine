#include "Player.h"
#include "Scene.h"
#include "AssetManager.h"
#include "Log.h"
#include "MathUtils.h"
#include "Block.h"
#include "Coin.h"

Player::Player(Transform2D transform) :
	GameActor(transform, ActorPlayer),
	mSprite(nullptr), mBoxCollider(nullptr), mPlayerComp(nullptr),
	mScore(0)
{
	Log::Info("Score : " + std::to_string(mScore));
};

void Player::Start()
{
	mSprite = GetComponent<AnimatedSpriteComponent>();

	mBoxCollider = GetComponent<BoxCollider2D>();

	mPlayerComp = GetComponent<PlayerComponent>();
}

void Player::Update()
{
	//flip x
	if (!MathUtils::NearZero(mPlayerComp->GetVelocity().x))
	{
		mSprite->SetFlipX(mPlayerComp->GetVelocity().x < 0);
	}

	//collisions
	bool CollidedWithGround = false;

	for (Block* block : mScene->GetActorsOfClass<Block>()) 
	{
		Vector2 collision = mBoxCollider->Collide(block->GetComponent<BoxCollider2D>());

		if (collision != Vector2::zero)
		{
			mTransform.position += collision;
			Vector2 axis = collision.normalized();
			Vector2 perpendicular = axis * mPlayerComp->GetVelocity().dot(axis);
			mPlayerComp->AddVelocity(-perpendicular);

			if (axis == Vector2::down)
			{
				CollidedWithGround = true;
			}
		}
	}

	mPlayerComp->SetGrounded(CollidedWithGround);


	for (Coin* coin : mScene->GetActorsOfClass<Coin>())
	{
		Vector2 collision = mBoxCollider->Collide(coin->GetComponent<BoxCollider2D>());

		if (collision != Vector2::zero)
		{
			coin->Destroy();
			mScore++;
			Log::Info("Score : " + std::to_string(mScore));
		}
	}

	//components
	for (ActorComponent* component : mComponents)
	{
		component->Update();
	}
}