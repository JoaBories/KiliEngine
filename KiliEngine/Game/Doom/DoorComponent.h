#pragma once
#include "Engine/Components/ActorComponent.h"

class DoorComponent : public ActorComponent
{
private:
    Vector3 mGoalPosition;
    float mInterpSpeed;
    bool mUp;
    bool mGoingUp;
    
protected:
    void OnUpdate() override;
    
public:
    DoorComponent(GameActor* pOwner, float pZMovement = 10.0f, float pInterpSpeed = 0.2f);
    
    void Up();
    
};
