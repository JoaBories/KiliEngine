#include "Map.h"

#include <fstream>
#include <iostream>

#include "AssetManager.h"
#include "Engine/Tools/Log.h"

using std::ifstream;

std::vector<std::string> BreakString(const std::string& pString, const char pSeparator)
{
    std::vector<std::string> r;
    std::string temp = pString;

    size_t pos = temp.find(pSeparator);

    while (pos != std::string::npos)
    {
        r.push_back(temp.substr(0, pos));
        temp = temp.substr(pos + 1);
        pos = temp.find(pSeparator);
    }

    r.push_back(temp);
    
    return r;
}

Map::Map(const std::string& pPath)
{
    std::string line;
    ifstream myFile;
    
    myFile.open(pPath);

    //Check for errors
    if (myFile.fail()) {
        Log::Info("Failed to open shader : " + pPath);
    }

    while (std::getline(myFile, line)) {
        switch (line[0])
        {
        case '$':
            Log::Info("Reading map : " + pPath + " with version : " + BreakString(line, ' ')[1]);
            break;
            
        case 'D' :
            ResolveDict(line);
            break;

        case 'F' :
            ResolveFloor(line);
            break;

        case 'V':
            ResolveVertex(line);
            break;

        case 'W':
            ResolveWall(line);
            break;
            
        case 'A':
            ResolveActor(line);
            
        default:
            break;
        }
        
    }

    myFile.close();
}

Texture* Map::GetTexture(const int pIndex)
{
    return AssetManager::GetTexture(mTextureMap[pIndex]);
}

void Map::ResolveDict(const std::string& pLine)
{
    auto dict = BreakString(BreakString(pLine, ' ')[1], ':');
    mTextureMap[std::stoi(dict[0])] = dict[1];
}

void Map::ResolveWall(const std::string& pLine)
{
    const auto brokeLine = BreakString(pLine, ' ');
    const int texture = std::stoi(brokeLine[3]);

    const auto brokePos = BreakString(brokeLine[4], ':');
    const auto brokeRot = BreakString(brokeLine[5], ':');
    const auto brokeScale = BreakString(brokeLine[6], ':');

    const Vector3 pos = Vector3(stof(brokePos[0]), std::stof(brokePos[1]), std::stof(brokePos[2]) * 25.0f) * MAP_SCALE;
    const Vector3 scale = Vector3(stof(brokeScale[0]), std::stof(brokeScale[1]), std::stof(brokeScale[2]) * 50.0f) * 0.5f * MAP_SCALE;

    MapWall wall = {texture, Transform(pos, Quaternion(), scale)};
    const float rotation = (stof(brokeRot[2]) + 90.0f) * MathUtils::DEG2RAD;
    wall.Transform.Rotate(Vector3::unitZ, rotation);
    mWalls.push_back(wall);
}

void Map::ResolveVertex(const std::string& pLine)
{
    const auto brokeLine = BreakString(pLine, ' ');
    const int indice = std::stoi(brokeLine[1]);

    const auto brokePos = BreakString(brokeLine[2], ':');
    const Vector3 pos = Vector3(stof(brokePos[0]), std::stof(brokePos[1]), 0.0f) * MAP_SCALE;

    mVertices[indice] = pos;
}

void Map::ResolveFloor(const std::string& pLine)
{
    const auto brokeLine = BreakString(pLine, ' ');

    const Vertex center = {Vector3::zero, Vector3::unitZ, {0.5f,0.5f}};
    std::vector<Vertex> vertices = {center};

    const int verticeCount = std::stoi(brokeLine[1]) + 1;
    vertices.reserve(verticeCount);

    const auto brokePos = BreakString(brokeLine[2], ':');
    const Vector3 pos = Vector3(stof(brokePos[0]), std::stof(brokePos[1]), 0.0f) * MAP_SCALE;
    
    const auto brokeVertices = BreakString(brokeLine[3], ':');

    float minX = MathUtils::INFINITY_POS;
    float maxX = MathUtils::INFINITY_NEG;
    float minY = MathUtils::INFINITY_POS;
    float maxY = MathUtils::INFINITY_NEG;
    
    for (const std::string& vertice : brokeVertices)
    {
        int indice = std::stoi(vertice);
        Vector3 position = mVertices[indice] - pos;

        minX = MathUtils::Min(minX, position.x);
        maxX = MathUtils::Max(maxX, position.x);
        minY = MathUtils::Min(minY, position.y);
        maxY = MathUtils::Max(maxY, position.y);
        
        vertices.push_back({position, Vector3::unitZ, {position.x / FLOOR_TILESIZE, position.y / FLOOR_TILESIZE}});
    }
    vertices.push_back(vertices[1]);

    int textureIndex = std::stoi(brokeLine[4]);

    const Vector3 offset = Vector3((minX + maxX) * 0.5f,
                                   (minY + maxY) * 0.5f, 0.0f);
    const Vector2 size = Vector2((MathUtils::Abs(minX) + MathUtils::Abs(maxX)) * 0.5f,
                                 (MathUtils::Abs(minY) + MathUtils::Abs(maxY)) * 0.5f);

    const float floorHeight = std::stof(brokeLine[5]);

    mFloors.push_back({textureIndex, pos, vertices, offset, size, floorHeight});
}

void Map::ResolveActor(const std::string& pLine)
{
    const auto brokeLine = BreakString(pLine, ' ');
    
    if (brokeLine[1] == "Door")
    {
        const auto brokePos = BreakString(brokeLine[2], ':');
        const Vector3 pos = Vector3(stof(brokePos[0])* MAP_SCALE, std::stof(brokePos[1])* MAP_SCALE, 5.0f) ;

        Transform door = Transform(pos, Quaternion(), Vector3::unit);
        
        const float rotation = (stof(brokeLine[3]) + 90.0f) * MathUtils::DEG2RAD;
        door.Rotate(Vector3::unitZ, rotation);
        
        mDoors.push_back(door);
    }
    else if (brokeLine[1] == "Demon")
    {
        const auto brokePos = BreakString(brokeLine[2], ':');
        const Vector3 pos = Vector3(stof(brokePos[0])* MAP_SCALE, std::stof(brokePos[1])* MAP_SCALE, 5.0f) ;
        
        mEnemies.push_back(pos);
    }
}
