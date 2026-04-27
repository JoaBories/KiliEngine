#pragma once
#include "Engine/GameActor.h"
#include "Utils/CollisionUtils.h"

class BulletTrace : public GameActor
{
private:
    float mDecaySpeed;

protected:
    void OnEarlyUpdate() override;
    
public:
    BulletTrace(const CollisionUtils::Line& pLinetrace, float pDecaySpeed);
    
};
