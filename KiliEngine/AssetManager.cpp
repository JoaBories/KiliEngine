#include "AssetManager.h"
#include "Log.h"
#include <sstream>

std::map<std::string, Texture*> AssetManager::mTextures = {};

Texture* AssetManager::LoadTexture(IRenderer* pRenderer, const std::string& pFileName, const std::string& pName)
{
    mTextures[pName] = LoadTextureFromFile(pRenderer, pFileName);
    return mTextures.at(pName);
}

Texture* AssetManager::GetTexture(const std::string& pName)
{
    if (mTextures.find(pName) == mTextures.end())
    {
        std::ostringstream loadError;
        loadError << "Texture " << pName << " does not exist in assets manager\n";
        Log::Error(LogType::Application, loadError.str());
        return nullptr;
    }
    return mTextures.at(pName);
}

ShaderProgram* AssetManager::LoadShader(const std::string& pName)
{
    mShaders[pName] = new ShaderProgram((pName + ".vert").c_str(), (pName + ".frag").c_str());
    return mShaders.at(pName);
}

ShaderProgram* AssetManager::GetShader(const std::string& pName)
{
    if (mShaders.find(pName) == mShaders.end())
    {
        std::ostringstream loadError;
        loadError << "Shader " << pName << " does not exist in assets manager\n";
        Log::Error(LogType::Application, loadError.str());
        return nullptr;
    }
    return mShaders.at(pName);
}

void AssetManager::Clear()
{
    for (auto iter : mTextures)
    {
        iter.second->Unload();
    }
    mTextures.clear();

    for (auto iter : mShaders)
    {
        iter.second->Unload();
    }
    mShaders.clear();
}

Texture* AssetManager::LoadTextureFromFile(IRenderer* pRenderer, const std::string& pFileName)
{
    Texture* texture = new Texture();
    texture->Load(pRenderer, pFileName);
    return texture;
}
