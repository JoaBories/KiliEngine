#pragma once

#include "Vector3.h"
#include "Struct.h"
using Struct::Vector2;

struct Vertex
{
    Vector3 Position;
    Vector3 Normal;
    Vector2 Uv;
};
