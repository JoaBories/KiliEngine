#include "Block.h"
#include "AssetManager.h"
#include "Log.h"


void Block::Start()
{
	mSprite = GetComponent<SpriteComponent>();

	mBoxCollider = GetComponent<BoxCollider2D>();
}

void Block::Update()
{
}
