#pragma once
#include "GameActor.h"
#include "GameRenderer.h"
#include "Scene.h"

#include "Utils.h"
using Struct::Vector2;

class Player :
    public GameActor
{

private:
    Vector2 mVelocity;
    float mAcceleration = 30.0f;
    bool mInput = false;

public:

    Player(Scene* scene, Transform2D transform) : 
        GameActor(scene, transform), mVelocity(Vector2::zero) {};

    // Inherited via GameActor
    void Start() override;
    void Update() override;
    void Render(const GameRenderer* renderer) override;

    void OnInputMove(float side);
};

