#pragma once
#include "GameActor.h"
#include "GameRenderer.h"
#include "Struct.h"

class Bullet :
    public GameActor
{

private:
    Vector2 mDirection;
    float mSpeed = 1.0f;

public:
    Bullet(Transform2D transform, Vector2 direction) :
        GameActor(transform), mDirection(direction) {};

    // Inherited via GameActor
    void Start() override;
    void Update() override;
};

