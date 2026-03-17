#pragma once

#include "Engine/GameActor.h"

class BowlingPin : public GameActor // Just an actor that will store a mesh component
{
public:
    BowlingPin(const Transform& pTransform) :
        GameActor(pTransform, "BowlingPin")
    {
    }
};