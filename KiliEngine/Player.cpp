#include "Player.h"
#include "Scene.h"
#include "AssetManager.h"
#include "Log.h"
#include "MathUtils.h"
#include "Block.h"

void Player::Start()
{
	std::vector<Texture*> anims;
	for (size_t i = 0; i < 22; i++)
	{
		anims.push_back(&AssetManager::GetTexture("run_" + std::to_string(i)));
	}

	mSprite = new AnimatedSpriteComponent(this, {Vector2::one, Vector2(0.5f,0.5f), 0}, anims, 30.0f);
	AddComponent(mSprite);

	mBoxCollider = new BoxCollider2D(this, 10, Rectangle{ Vector2::zero, Vector2(60,60) });
	AddComponent(mBoxCollider);

	mPlayerComp = new PlayerComponent(this, 10);
	AddComponent(mPlayerComp);
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