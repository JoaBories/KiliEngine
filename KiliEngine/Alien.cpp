#include "Alien.h"
#include "BoxCollider2D.h"
#include "Log.h"

using Struct::Vector2;

void Alien::Start()
{
	AddComponent(new BoxCollider2D(this, 10, Rectangle{ Vector2::zero, Vector2(50,50) }));
}

void Alien::Update()
{
}