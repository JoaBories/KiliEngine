#pragma once
#include "GameActor.h"
#include "GameRenderer.h"
#include "Scene.h"

#include "AnimatedSpriteComponent.h"
#include "BoxCollider2D.h"
#include "MoveComponent.h"

#include "Struct.h"
using Struct::Vector2;

class Player :
    public GameActor
{

private:
    float mAcceleration = 30.0f;

    AnimatedSpriteComponent* mSprite;
    BoxCollider2D* mBoxCollider;
    MoveComponent* mMoveComp;

public:

    Player(Transform2D transform) : 
        GameActor(transform)
    {};

    // Inherited via GameActor
    void Start() override;
    void Update() override;
};

