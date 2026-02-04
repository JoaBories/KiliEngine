#include "Player.h"
#include "Scene.h"
#include "AssetManager.h"
#include "Log.h"
#include "MathUtils.h"
#include "Block.h"

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
	Rectangle playerRect = mBoxCollider->GetBoxCollider().toObjectSpace(mTransform);

	for (Block* block : mScene->GetActorsOfClass<Block>()) 
	{
		Rectangle blockRect = block->GetComponent<BoxCollider2D>()->GetBoxCollider().toObjectSpace(block->GetTransform());
		
		Vector2 collision = playerRect.CheckAABB(blockRect);
		if (collision != Vector2::zero)
		{
			mTransform.position += collision / 2;
			Vector2 axis = collision.normalized();
			Vector2 perpendicular = axis * mPlayerComp->GetVelocity().dot(axis);
			mPlayerComp->AddVelocity(-perpendicular);

			if (axis == Vector2::down)
			{
				mPlayerComp->SetGrounded(true);
			}
		}
	}

	//components
	for (ActorComponent* component : mComponents)
	{
		component->Update();
	}
}