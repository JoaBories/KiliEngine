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

    int pos = temp.find(pSeparator);

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

    //Open file of this name
    ifstream myFile;
    myFile.open(pPath);

    //Check for errors
    if (myFile.fail()) {
        Log::Info("Failed to open shader : " + pPath);
    }

    while (std::getline(myFile, line)) {
        char identifier = line[0];

        switch (identifier)
        {
        case '$':
            Log::Info("Reading map with version : " + BreakString(line, ' ')[1]);
            break;
            
        case 'D' :
            ResolveDict(line);
            break;

        case 'V':
            break;

        case 'W':
            ResolveWall(line);
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
    auto brokeLine = BreakString(pLine, ' ');
    int texture = std::stoi(brokeLine[3]);
    
    auto brokePos = BreakString(brokeLine[4], ':');
    auto brokeRot = BreakString(brokeLine[5], ':');
    auto brokeScale = BreakString(brokeLine[6], ':');

    Vector3 pos = Vector3(stof(brokePos[0]), std::stof(brokePos[1]), std::stof(brokePos[2]) + 2.0f) * 0.2f;
    Vector3 scale = Vector3(stof(brokeScale[0]), std::stof(brokeScale[1]), std::stof(brokeScale[2])) * 0.5f * 0.2f;

    MapWall wall = {texture, Transform(pos, Quaternion(), scale)};
    float rotation = (stof(brokeRot[2]) + 90.0f) * MathUtils::DEG2RAD;
    wall.Transform.Rotate(Vector3::unitZ, rotation);
    mWalls.push_back(wall);
}
