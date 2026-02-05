#pragma once
#include "GameActor.h"

#include "SpriteComponent.h"
#include "BoxCollider2D.h"

class Coin : public GameActor
{
private:
	SpriteComponent* mSprite;
	BoxCollider2D* mBoxCollider;

public:
	Coin(Transform2D pTransform) :
		GameActor(pTransform, ActorCoin),
		mSprite(nullptr), mBoxCollider(nullptr)
	{
	};

	void Start() override;
	void Update() override;
};

