#pragma once
#include "GameActor.h"

class Floor : public GameActor
{
public:
    Floor(const Transform& pTransform) :
        GameActor(pTransform)
    {
    }
    
};