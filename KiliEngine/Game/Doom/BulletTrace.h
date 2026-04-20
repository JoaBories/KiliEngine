#pragma once
#include "Engine/GameActor.h"
#include "Utils/CollisionUtils.h"

class BulletTrace : public GameActor
{
private:
    float mTime;
    
protected:
    
public:
    BulletTrace(const CollisionUtils::Line& pLinetrace);
    
};
