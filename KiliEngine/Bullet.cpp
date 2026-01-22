#include "Bullet.h"
#include "Time.h"
#include "BoxCollider2D.h"
#include "GameRenderer.h"
#include "Utils.h"

void Bullet::Start()
{
}

void Bullet::Update()
{
	mTransform.position += mDirection * mSpeed * Time::deltaTime * 1000.0f;
}

void Bullet::Render(const GameRenderer* renderer)
{
	renderer->DrawRect(
		GetComponent<BoxCollider2D>()->GetBoxCollider().toObjectSpace(mTransform),
		Color::WHITE);
}
