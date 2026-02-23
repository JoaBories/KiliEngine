#pragma once
#include "GameActor.h"

class EnviroActor : public GameActor // Just an actor that will store a mesh component
{
public:
    EnviroActor(const Transform& pTransform) :
        GameActor(pTransform)
    {
    }
    
};
