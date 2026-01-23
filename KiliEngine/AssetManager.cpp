#include "AssetManager.h"
#include "Log.h"
#include <sstream>

std::map<std::string, Texture> AssetManager::mTextures = {};

Texture AssetManager::LoadTexture(GameRenderer& pRenderer, const std::string& pFileName, const std::string& pName)
{
    mTextures[pName] = LoadTextureFromFile(pRenderer, pFileName);
    return mTextures.at(pName);
}

Texture& AssetManager::GetTexture(const std::string& pName)
{
    if (mTextures.find(pName) == mTextures.end())
    {
        std::ostringstream loadError;
        loadError << "Texture " << pName << " does not exist in assets manager\n";
        Log::Error(LogType::Application, loadError.str());
    }
    return mTextures[pName];
}

void AssetManager::Clear()
{
    for (auto iter : mTextures)
    {
        iter.second.Unload();
    }
    mTextures.clear();
}

Texture AssetManager::LoadTextureFromFile(GameRenderer& pRenderer, const std::string& pFileName)
{
    Texture texture;
    texture.Load(pRenderer, pFileName);
    return texture;
}
