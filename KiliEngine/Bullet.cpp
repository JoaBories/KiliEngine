#include "Bullet.h"
#include "Time.h"
#include "BoxCollider2D.h"
#include "GameRenderer.h"
#include "Struct.h"
#include "SpriteComponent.h"
#include "AssetManager.h"

void Bullet::Start()
{
	AddComponent(new SpriteComponent(this, AssetManager::GetTexture("ball"), Transform2D{Vector2::zero, Vector2(0.1f, 0.1f)}, 10));
}

void Bullet::Update()
{
	mTransform.position += mDirection * mSpeed * Time::deltaTime * 1000.0f;
}

void Bullet::Render(const GameRenderer* renderer)
{
	renderer->DrawRect(Rectangle{ mTransform.position, Vector2(5, 20) * mTransform.scale, 0.0f }, {255,255,0,255});
}
