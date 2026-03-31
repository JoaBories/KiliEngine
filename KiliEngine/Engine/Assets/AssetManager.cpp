#include "AssetManager.h"
#include "Engine/Tools/Log.h"
#include "Engine/Config.h"
#include "Libraries/tiny_obj_loader.h"

#include <chrono>
using clk = std::chrono::high_resolution_clock;
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

            case AssetMaterial:
                FetchMaterial(entry.path());
                break;

            case AssetMap:
                FetchMap(entry.path());
                break;
        }
    }
}

GlRenderer* AssetManager::mRenderer = nullptr;

std::map<std::string, Texture*> AssetManager::mLoadedTextures = {};
std::map<std::string, Shader*> AssetManager::mLoadedShaders = {};
std::map<std::string, Mesh*> AssetManager::mLoadedMeshes = {};
std::map<std::string, Material*> AssetManager::mLoadedMaterials = {};
std::map<std::string, Map*> AssetManager::mLoadedMaps = {};

std::map<std::string, path> AssetManager::mUnloadedTextures = {};
std::map<std::string, path> AssetManager::mUnloadedShaders = {};
std::map<std::string, path> AssetManager::mUnloadedMeshes = {};
std::map<std::string, path> AssetManager::mUnloadedMaterials = {};
std::map<std::string, path> AssetManager::mUnloadedMaps = {};

Mesh* AssetManager::LoadMeshFromFile(const std::string& pFilePath)
{
    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warning, errors;
    bool success = LoadObj(&attributes, &shapes, &materials, &warning, &errors, pFilePath.c_str());
    if(!success)
    {
        Log::Error(LogType::Application, "Mesh "+ pFilePath + " does not exist or is not .obj");
        return nullptr;
    }
    else
    {
        Log::Info("Mesh "+ pFilePath +" successfully loaded");
    }
    std::vector<Vertex> vertices;

    for (auto& shape : shapes)
    {
        tinyobj::mesh_t &mesh = shape.mesh;
        for (auto [vertex_index, normal_index, texcoord_index] : mesh.indices)
        {
            Vector3 position = Vector3{
                attributes.vertices[vertex_index * 3],
                attributes.vertices[vertex_index * 3 + 2],
                attributes.vertices[vertex_index * 3 + 1]
            };
            Vector3 normal = Vector3{
                attributes.normals[normal_index * 3],
                attributes.normals[normal_index * 3 + 1],
                attributes.normals[normal_index * 3 + 2]
            };
            Vector2 texCoord = {
                attributes.texcoords[texcoord_index * 2],
                attributes.texcoords[texcoord_index * 2 + 1]
            };
            Vertex vertex = Vertex{position, normal, texCoord};
            vertices.push_back(vertex);
        }
    }

    Mesh* loadedMesh = new Mesh(vertices);
    loadedMesh->AddTexture(GetTexture("DefaultTexture"));
    return loadedMesh;
}

Material* AssetManager::LoadMaterialFromFile(const std::string& pFilePath)
{
    std::vector<Shader*> shaders;
    std::string shadersForLog;
    std::string line;

    //Open file of this name
    std::ifstream myFile;
    myFile.open(pFilePath);

    //Check for errors
    if (myFile.fail()) {
        Log::Error(LogType::Render, "Failed to open shader : " + pFilePath);
    }

    while (std::getline(myFile, line)) {
        shaders.push_back(GetShader(line));
        shadersForLog += line + ", ";
    }

    myFile.close();

    Material* loadedMaterial = new Material(shaders);
    Log::Info("Material "+ pFilePath + " loaded with : " + shadersForLog);
    return loadedMaterial;
}

void AssetManager::Init(GlRenderer* pRenderer)
{
    mRenderer = pRenderer;
    
    FetchAll();
}

void AssetManager::Close()
{
    UnloadAll();
    UnfetchAll();
}

void AssetManager::FetchAll()
{
    Log::Info("==========| Start fetching Files");
    const auto startTime = clk::now();

    UnfetchAll();
    
    SearchAFolderFor(path(Cfg::TEXTURE_PATH), AssetTexture);
    SearchAFolderFor(path(Cfg::SHADER_PATH), AssetShader);
    SearchAFolderFor(path(Cfg::MESH_PATH), AssetMesh);
    SearchAFolderFor(path(Cfg::MATERIAL_PATH), AssetMaterial);
    SearchAFolderFor(path(Cfg::MAP_PATH), AssetMap);

    const auto endTime = clk::now();
    const std::string time = std::to_string(std::chrono::duration<double>(endTime - startTime).count());
    Log::Info("==========| Finish fetching Files in : " + time + "s");
}

void AssetManager::UnfetchAll()
{
    mUnloadedTextures.clear();
    mUnloadedShaders.clear();
    mUnloadedMeshes.clear();
    mUnloadedMaterials.clear();
    mUnloadedMaps.clear();
}

void AssetManager::LoadAll()
{
    Log::Info("==========| Start loading Files");
    const auto startTime = clk::now();
    
    UnloadAll();

    for (auto& unloadedPath : mUnloadedTextures) LoadTexture(unloadedPath.first);
    
    for (auto& unloadedPath : mUnloadedShaders) LoadShader(unloadedPath.first);
    
    for (auto& unloadedPath : mUnloadedMaterials) LoadMaterial(unloadedPath.first);
    
    for (auto& unloadedPath : mUnloadedMeshes) LoadMesh(unloadedPath.first);

    for (auto& unloadedPath : mUnloadedMaps) LoadMap(unloadedPath.first);
    
    const auto endTime = clk::now();
    const std::string time = std::to_string(std::chrono::duration<double>(endTime - startTime).count());
    Log::Info("==========| Finish loading Files in : " + time + "s");
}

void AssetManager::UnloadAll()
{
    for (const auto& [name, texture] : mLoadedTextures)
    {
        texture->Unload();
        delete texture;
    }
    mLoadedTextures.clear();

    for (const auto& [name, Shader] : mLoadedShaders)
    {
        Shader->Unload();
        delete Shader;
    }
    mLoadedShaders.clear();
    
    for (const auto& [name, mesh] : mLoadedMeshes)
    {
        mesh->Unload();
        delete mesh;
    }
    mLoadedMeshes.clear();

    for (const auto& [name, material] : mLoadedMaterials)
    {
        delete material;
    }
    mLoadedMaterials.clear();

    for (const auto& [name, map] : mLoadedMaps)
    {
        delete map;
    }
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
            return GetTexture("DefaultTexture");
        }
        
        return LoadTexture(pName);
    }
    return mLoadedTextures.at(pName);
}

void AssetManager::FetchShader(const path& pShaderPath)
{
    if (Shader::IsSupported(pShaderPath.extension().string()))
    {
        const std::string name = pShaderPath.filename().string();
        if (mLoadedShaders.find(name) == mLoadedShaders.end())
        {
            mUnloadedShaders[name] = pShaderPath;
        }
    }
}

Shader* AssetManager::LoadShader(const std::string& pName)
{
    const std::string shaderPath = mUnloadedShaders.at(pName).string();
    mLoadedShaders[pName] = new Shader(shaderPath, Shader::GetShaderType(mUnloadedShaders.at(pName).extension().string()));
    return mLoadedShaders.at(pName);
}

Shader* AssetManager::GetShader(const std::string& pName)
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

void AssetManager::FetchMaterial(const path& pMaterialPath)
{
    if (pMaterialPath.extension() == ".mat")
    {
        const std::string name = pMaterialPath.filename().replace_extension("").string();
        if (mLoadedMaterials.find(name) == mLoadedMaterials.end())
        {
            mUnloadedMaterials[name] = pMaterialPath;
        }
    }
}

Material* AssetManager::LoadMaterial(const std::string& pName)
{
    const std::string materialPath = mUnloadedMaterials.at(pName).string();
    mLoadedMaterials[pName] = LoadMaterialFromFile(materialPath);
    return mLoadedMaterials.at(pName);
}

Material* AssetManager::GetMaterial(const std::string& pName)
{
    if (mLoadedMaterials.find(pName) == mLoadedMaterials.end())
    {
        if (mUnloadedMaterials.find(pName) == mUnloadedMaterials.end())
        {
            Log::Error(LogType::Application,"Material " + pName + " does not exist in assets manager");
            return nullptr;
        }
        
        return LoadMaterial(pName);
    }
    return mLoadedMaterials.at(pName);
}

void AssetManager::FetchMap(const path& pMapPath)
{
    if (pMapPath.extension() == ".txt")
    {
        const std::string name = pMapPath.filename().replace_extension("").string();
        if (mLoadedMaps.find(name) == mLoadedMaps.end())
        {
            mUnloadedMaps[name] = pMapPath;
        }
    }
}

Map* AssetManager::LoadMap(const std::string& pName)
{
    const std::string mapPath = mUnloadedMaps.at(pName).string();
    mLoadedMaps[pName] = new Map(mapPath);
    return mLoadedMaps.at(pName);
}

Map* AssetManager::GetMap(const std::string& pName)
{
    if (mLoadedMaps.find(pName) == mLoadedMaps.end())
    {
        if (mUnloadedMaps.find(pName) == mUnloadedMaps.end())
        {
            Log::Error(LogType::Application,"Map " + pName + " does not exist in assets manager");
            return nullptr;
        }
        
        return LoadMap(pName);
    }
    return mLoadedMaps.at(pName);
}
