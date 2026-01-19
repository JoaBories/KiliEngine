#pragma once
#include "GameActor.h"

#include "Utils.h"
using Struct::Vector2;

class Player :
    public GameActor
{

private:
    Vector2 mVelocity;
    float mMaxSpeed = 400.0f;
    float mAcceleration = 1000.0f;
    bool mInput = false;

public:

    Player(Scene& scene, Transform2D transform) : GameActor(scene, transform), mVelocity(Vector2::zero) {};

    // Inherited via GameActor
    void Start() override;
    void SetActive(ActorState newState) override;
    void Update() override;
    void Render() override;
    void Destroy() override;

};

