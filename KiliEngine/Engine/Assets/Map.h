#pragma once
#include <map>
#include <string>
#include <vector>

#include "Engine/Transform.h"

class Texture;

struct MapWall
{
    int TextureIndex;
    Transform Transform;
};

class Map
{

private:
    std::map<int, std::string> mTextureMap;
    std::vector<MapWall> mWalls;

    void ResolveDict(const std::string& pLine);
    void ResolveWall(const std::string& pLine);
    
public:
    Map() = delete;
    Map(const std::string& pPath);

    [[nodiscard]] std::vector<MapWall> GetWalls() const { return mWalls;}
    Texture* GetTexture(int pIndex);
};
