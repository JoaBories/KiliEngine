#pragma once
#include "Engine/GameActor.h"
#include "Engine/Components/RigidBody.h"

class Player : public GameActor
{
private:
    RigidBody* mRb;
    float mSpeed;
    
protected:
    void OnStart() override;
    void OnEarlyUpdate() override;
    
public:
    Player();
    explicit Player(const Transform& pTransform, float pSpeed);
};
