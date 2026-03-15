#pragma once
#include "ActorComponent.h"

class FreeCamComponent : public ActorComponent
{    
protected:
    float mSpeed;
    float mSensibility;
    
    void OnUpdate() override;
    
public:
    FreeCamComponent(GameActor* pOwner, float pSpeed, float pSensibility);
    
};
