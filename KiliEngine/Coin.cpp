#include "Coin.h"

void Coin::Start()
{
	mSprite = GetComponent<SpriteComponent>();

	mBoxCollider = GetComponent<BoxCollider2D>();
}

void Coin::Update()
{
}
