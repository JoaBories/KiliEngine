#include "Bullet.h"
#include "Time.h"
#include "BoxCollider2D.h"
#include "GameRenderer.h"
#include "Struct.h"
#include "SpriteComponent.h"
#include "AssetManager.h"

void Bullet::Start()
{
	AddComponent(new SpriteComponent(this, Transform2D{ Vector2::zero, Vector2(0.1f, 0.1f) }, AssetManager::GetTexture("ball"), 10));
}

void Bullet::Update()
{
	mTransform.position += mDirection * mSpeed * Time::deltaTime * 1000.0f;
}
