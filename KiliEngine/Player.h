#pragma once
#include "GameActor.h"
#include "GameRenderer.h"
#include "Scene.h"

#include "AnimatedSpriteComponent.h"
#include "BoxCollider2D.h"
#include "PlayerComponent.h"

#include "Struct.h"
using Struct::Vector2;

class Player :
    public GameActor
{

private:
    AnimatedSpriteComponent* mSprite;
    BoxCollider2D* mBoxCollider;
    PlayerComponent* mPlayerComp;

    int mScore;

public:

    Player(Transform2D transform);

    // Inherited via GameActor
    void Start() override;
    void Update() override;

    int GetScore() const { return mScore; };
};

