#include "Player.h"
#include "Scene.h"
#include "AssetManager.h"
#include "Log.h"
#include "MathUtils.h"

void Player::Start()
{
	std::vector<Texture*> anims;
	for (size_t i = 0; i < 22; i++)
	{
		anims.push_back(&AssetManager::GetTexture("run_" + std::to_string(i)));
	}

	mSprite = new AnimatedSpriteComponent(this, {Vector2::one, Vector2(0.5f,0.5f), 0}, anims, 30.0f);
	AddComponent(mSprite);

	mBoxCollider = new BoxCollider2D(this, 10, Rectangle{ Vector2::zero, Vector2(50,50) });
	AddComponent(mBoxCollider);

	mPlayerComp = new PlayerComponent(this, 10);
	AddComponent(mPlayerComp);
}

void Player::Update()
{
	for (ActorComponent* component : mComponents)
	{
		component->Update();
	}

	if (!MathUtils::NearZero(mPlayerComp->GetVelocity().x))
	{
		mSprite->SetFlipX(mPlayerComp->GetVelocity().x < 0);
	}
}