#pragma once
#include "GameActor.h"
#include "ICollideable.h"
#include "IInput.h"

class Player :
    public GameActor,
    public ICollideable,
    public IInput
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


    // Inherited via ICollideable
    void Collide(GameActor& other, Vector2 overlap) override;


    // Inherited via IInput
    void OnInput(SDL_Event input) override;

};

