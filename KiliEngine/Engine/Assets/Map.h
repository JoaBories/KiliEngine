#pragma once
#include <map>
#include <string>
#include <vector>

#include "Engine/Transform.h"
#include "Utils/Vertex.h"

class Texture;

constexpr float MAP_SCALE = 0.2f;
constexpr float FLOOR_TILESIZE = 8.0f;

struct MapWall
{
    int TextureIndex;
    Transform Transform;
};

struct MapFloor
{
    int TextureIndex;
    Vector3 Position;
    std::vector<Vertex> Vertices;
    Vector3 ColliderOffset;
    Vector2 ColliderSize;
};

class Map
{

private:
    std::map<int, std::string> mTextureMap;
    std::vector<MapWall> mWalls;
    std::vector<MapFloor> mFloors;
    std::map<int, Vector3> mVertices;

    void ResolveDict(const std::string& pLine);
    void ResolveWall(const std::string& pLine);
    void ResolveVertex(const std::string& pLine);
    void ResolveFloor(const std::string& pLine);
    
public:
    Map() = delete;
    Map(const std::string& pPath);

    [[nodiscard]] std::vector<MapWall> GetWalls() const { return mWalls;}
    [[nodiscard]] std::vector<MapFloor> GetFloors() const { return mFloors;}
    [[nodiscard]] std::map<int, Vector3> GetVertices() const { return mVertices;}
    Texture* GetTexture(int pIndex);
};
