#pragma once
#include "GameActor.h"
#include "Tools/GameTime.h"

class EnviroActor : public GameActor // Just an actor that will store a mesh component
{

protected:

    void OnEarlyUpdate() override
    {
        Rotate(Vector3::unitX, 1 * MathUtils::DEG2RAD);
    }
    
public:
    EnviroActor(const Transform& pTransform) :
        GameActor(pTransform, "EnviroActor")
    {
    }
    
};
