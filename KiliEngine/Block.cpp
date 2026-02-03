#include "Block.h"
#include "AssetManager.h"
#include "Log.h"


void Block::Start()
{
	mSprite = new SpriteComponent(this, Transform2D{Vector2::zero, Vector2(4.0f,4.0f), 0}, AssetManager::GetTexture("box"));
	AddComponent(mSprite);

	mBoxCollider = new BoxCollider2D(this, 10, Rectangle{ Vector2::zero, Vector2(64,64) });
	AddComponent(mBoxCollider);
}

void Block::Update()
{
}
