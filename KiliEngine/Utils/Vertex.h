#pragma once

#include "Vector3.h"
#include "Struct.h"
using Struct::Vector2;

struct Vertex
{
    Vector3 Position;
    Vector3 Normal;
    Vector2 Uv;

    float* ToVerticeArray(const std::vector<Vertex>& pVertices);
};
    
inline float* ToVerticeArray(const std::vector<Vertex>& pVertices)
{
    const auto array = new float[pVertices.size() * 8];
    int counter = 0;
    for (auto& [Position, Normal, Uv] : pVertices)
    {
        array[counter+0] = Position.x;
        array[counter+1] = Position.y;
        array[counter+2] = Position.z;
        array[counter+3] = Normal.x;
        array[counter+4] = Normal.y;
        array[counter+5] = Normal.z;
        array[counter+6] = Uv.x;
        array[counter+7] = Uv.y;
        counter += 8;
    }
    return array;
}
