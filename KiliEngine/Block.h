#pragma once
#include "GameActor.h"

#include "SpriteComponent.h"
#include "BoxCollider2D.h"

class Block : public GameActor
{
private:
	SpriteComponent* mSprite;
	BoxCollider2D* mBoxCollider;

public:
	Block(Transform2D pTransform) :
		GameActor(pTransform, ActorBlock),
		mSprite(nullptr), mBoxCollider(nullptr)
	{
	};

	void Start() override;
	void Update() override;
};

