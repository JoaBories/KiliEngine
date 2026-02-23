#include "AssetManager.h"
#include "Log.h"
#include "Config.h"

#include <chrono>
using Clk = std::chrono::high_resolution_clock;
using namespace std::filesystem;

void AssetManager::SearchAFolderFor(const path& pFolderPath, const AssetType pForWhat)
{
    for (const auto& entry : directory_iterator(pFolderPath))
    {
        if (entry.is_directory())
        {
            SearchAFolderFor(entry.path(), pForWhat);
            continue;
        }

        switch (pForWhat)
        {
        case AssetTexture:
            FetchTexture(entry.path());
            break;
            
        case AssetShader:
            FetchShader(entry.path());
            break;

        case AssetMesh:
            FetchMesh(entry.path());
            break;
        }
    }
}

IRenderer* AssetManager::mRenderer = nullptr;

std::map<std::string, Texture*> AssetManager::mLoadedTextures = {};
std::map<std::string, ShaderProgram*> AssetManager::mLoadedShaders = {};
std::map<std::string, Mesh*> AssetManager::mLoadedMeshes = {};

std::map<std::string, path> AssetManager::mUnloadedTextures = {};
std::map<std::string, path> AssetManager::mUnloadedShaders = {};
std::map<std::string, path> AssetManager::mUnloadedMeshes = {};

Mesh* AssetManager::LoadMeshFromFile(const std::string& pName)
{
}

void AssetManager::Init(IRenderer* pRenderer)
{
    mRenderer = pRenderer;
    
    FetchAll();
    
    LoadShader("Basic");
    LoadShader("Sprite");
}

void AssetManager::Close()
{
    UnloadAll();
    UnfetchAll();
}

void AssetManager::FetchAll()
{
    Log::Info("==========| Start fetching Files");
    const auto startTime = Clk::now();

    UnfetchAll();
    
    SearchAFolderFor(path(TEXTURE_PATH), AssetTexture);
    SearchAFolderFor(path(SHADER_PATH), AssetShader);
    SearchAFolderFor(path(MESH_PATH), AssetMesh);

    const auto endTime = Clk::now();
    const std::string time = std::to_string(std::chrono::duration<double>(endTime - startTime).count());
    Log::Info("==========| Finish fetching Files in : " + time + "s");
}

void AssetManager::UnfetchAll()
{
    mUnloadedTextures.clear();
    mUnloadedShaders.clear();
    mUnloadedMeshes.clear();
}

void AssetManager::LoadAll()
{
    Log::Info("==========| Start loading Files");
    const auto startTime = Clk::now();
    
    UnloadAll();

    for (auto& unloadedPath : mUnloadedTextures)
    {
        LoadTexture(unloadedPath.first);
    }
    
    for (auto& unloadedPath : mUnloadedShaders)
    {
        LoadShader(unloadedPath.first);
    }
    
    for (auto& unloadedPath : mUnloadedMeshes)
    {
        LoadMesh(unloadedPath.first);
    }
    
    const auto endTime = Clk::now();
    const std::string time = std::to_string(std::chrono::duration<double>(endTime - startTime).count());
    Log::Info("==========| Finish loading Files in : " + time + "s");
}

void AssetManager::UnloadAll()
{
    for (const auto& iter : mLoadedTextures)
    {
        iter.second->Unload();
    }
    mLoadedTextures.clear();

    for (const auto& iter : mLoadedShaders)
    {
        iter.second->Unload();
    }
    mLoadedShaders.clear();
    
    for (const auto& iter : mLoadedMeshes)
    {
        iter.second->Unload();
    }
    mLoadedMeshes.clear();
}

void AssetManager::FetchTexture(const path& pTexturePath)
{
    if (pTexturePath.extension() == ".png" || pTexturePath.extension() == ".jpg")
    {
        const std::string name = pTexturePath.filename().replace_extension("").string();
        if (mLoadedTextures.find(name) == mLoadedTextures.end())
        {
            mUnloadedTextures[name] = pTexturePath;
        }
    }
}

Texture* AssetManager::LoadTexture(const std::string& pName)
{
    if (mUnloadedTextures.find(pName) == mUnloadedTextures.end()) return nullptr;
    const path texturePath = mUnloadedTextures.at(pName); 
    
    Texture* texture = new Texture(); // todo move this in the constructor
    texture->Load(mRenderer, texturePath.string());
    mLoadedTextures[pName] = texture;
    return mLoadedTextures.at(pName);
}

Texture* AssetManager::GetTexture(const std::string& pName)
{
    if (mLoadedTextures.find(pName) == mLoadedTextures.end())
    {
        if (mUnloadedTextures.find(pName) == mUnloadedTextures.end())
        {
            Log::Error(LogType::Application, "Texture " + pName + " does not exist in fetched textures");
            return nullptr;
        }
        
        return LoadTexture(pName);
    }
    return mLoadedTextures.at(pName);
}

void AssetManager::FetchShader(const path& pShaderPath)
{
    if (pShaderPath.extension() == ".vert") // todo perhaps handling this with a txt file .shader
    {
        const std::string name = pShaderPath.filename().replace_extension("").string();
        if (mLoadedShaders.find(name) == mLoadedShaders.end())
        {
            mUnloadedShaders[name] = pShaderPath;
        }
    }
}

ShaderProgram* AssetManager::LoadShader(const std::string& pName)
{
    const std::string shaderPath = mUnloadedShaders.at(pName).replace_extension("").string();
    mLoadedShaders[pName] = new ShaderProgram(shaderPath + ".vert", shaderPath + ".frag");
    return mLoadedShaders.at(pName);
}

ShaderProgram* AssetManager::GetShader(const std::string& pName)
{
    if (mLoadedShaders.find(pName) == mLoadedShaders.end())
    {
        if (mUnloadedShaders.find(pName) == mUnloadedShaders.end())
        {
            Log::Error(LogType::Application,"Shader " + pName + " does not exist in assets manager");
            return nullptr;
        }
        
        return LoadShader(pName);
    }
    return mLoadedShaders.at(pName);
}

void AssetManager::FetchMesh(const path& pMeshPath)
{
    if (pMeshPath.extension() == ".obj")
    {
        const std::string name = pMeshPath.filename().replace_extension("").string();
        if (mLoadedMeshes.find(name) == mLoadedMeshes.end())
        {
            mUnloadedMeshes[name] = pMeshPath;
        }
    }
}

Mesh* AssetManager::LoadMesh(const std::string& pName)
{
    const std::string meshPath = mUnloadedMeshes.at(pName).string();
    mLoadedMeshes[pName] = LoadMeshFromFile(meshPath);
    return mLoadedMeshes.at(pName);
}

Mesh* AssetManager::GetMesh(const std::string& pName)
{
    if (mLoadedMeshes.find(pName) == mLoadedMeshes.end())
    {
        if (mUnloadedMeshes.find(pName) == mUnloadedMeshes.end())
        {
            Log::Error(LogType::Application,"Mesh " + pName + " does not exist in assets manager");
            return nullptr;
        }
        
        return LoadMesh(pName);
    }
    return mLoadedMeshes.at(pName);
}
