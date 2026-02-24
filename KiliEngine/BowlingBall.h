#pragma once

#include "GameActor.h"

class BowlingBall : public GameActor // Just an actor that will store a mesh component
{
public:
    BowlingBall(const Transform& pTransform) :
        GameActor(pTransform)
    {
    }

protected:
    void OnLateUpdate() override;
    void OnStart() override;
};