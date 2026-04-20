#pragma once
#include "Engine/GameActor.h"
#include "Utils/CollisionUtils.h"

class BulletTrace : public GameActor
{    
protected:
    void OnEarlyUpdate() override;
    
public:
    BulletTrace(const CollisionUtils::Line& pLinetrace);
    
};
