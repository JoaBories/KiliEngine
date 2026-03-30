#pragma once
#include "GameActor.h"

class EmptyActor : public GameActor
{
public:
    EmptyActor(const Transform& pTransform, const std::string& pName = "EmptyActor", ActorTags pTag = ActorDefault);
    
};
