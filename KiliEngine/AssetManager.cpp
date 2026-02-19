#include "AssetManager.h"
#include "Log.h"
#include <sstream>

std::map<std::string, Texture*> AssetManager::Textures = {};
std::map<std::string, ShaderProgram*> AssetManager::Shaders = {};

Texture* AssetManager::LoadTexture(IRenderer* pRenderer, const std::string& pFileName, const std::string& pName)
{
    Texture* texture = new Texture();
    texture->Load(pRenderer, TexturePath + pFileName);
    Textures[pName] = texture;
    return Textures.at(pName);
}

Texture* AssetManager::GetTexture(const std::string& pName)
{
    if (Textures.find(pName) == Textures.end())
    {
        std::ostringstream loadError;
        loadError << "Texture " << pName << " does not exist in assets manager\n";
        Log::Error(LogType::Application, loadError.str());
        return nullptr;
    }
    return Textures.at(pName);
}

ShaderProgram* AssetManager::LoadShader(const std::string& pName)
{
    Shaders[pName] = new ShaderProgram((ShaderPath + pName + ".vert").c_str(), (ShaderPath + pName + ".frag").c_str());
    return Shaders.at(pName);
}

ShaderProgram* AssetManager::GetShader(const std::string& pName)
{
    if (Shaders.find(pName) == Shaders.end())
    {
        std::ostringstream loadError;
        loadError << "Shader " << pName << " does not exist in assets manager\n";
        Log::Error(LogType::Application, loadError.str());
        return nullptr;
    }
    return Shaders.at(pName);
}

void AssetManager::Clear()
{
    for (const auto& iter : Textures)
    {
        iter.second->Unload();
    }
    Textures.clear();

    for (const auto& iter : Shaders)
    {
        iter.second->Unload();
    }
    Shaders.clear();
}
