#pragma once

#include "Texture.h"
#include "Mesh.h"
#include "Material.h"
#include <map>

#include <filesystem>

#include "Map.h"
using std::filesystem::path;

#define TINYOBJLOADER_IMPLEMENTATION

enum AssetType : Uint8
{
	AssetTexture,
	AssetShader,
	AssetMesh,
	AssetMaterial,
	AssetMap,
};

class AssetManager
{
private:
	AssetManager() = default;

	static void SearchAFolderFor(const path& pFolderPath, AssetType pForWhat);
	
	static GlRenderer* mRenderer;
	
	static std::map<std::string, Texture*> mLoadedTextures;
	static std::map<std::string, Shader*> mLoadedShaders;
	static std::map<std::string, Mesh*> mLoadedMeshes;
	static std::map<std::string, Material*> mLoadedMaterials;
	static std::map<std::string, Map*> mLoadedMaps;
	
	static std::map<std::string, path> mUnloadedTextures;
	static std::map<std::string, path> mUnloadedShaders;
	static std::map<std::string, path> mUnloadedMeshes;
	static std::map<std::string, path> mUnloadedMaterials;
	static std::map<std::string, path> mUnloadedMaps;
	
	static Mesh* LoadMeshFromFile(const std::string& pFilePath);
	static Material* LoadMaterialFromFile(const std::string& pFilePath);
	
public:
	
	static void Init(GlRenderer* pRenderer);
	static void Close();
	
	static void FetchAll();
	static void UnfetchAll();
	static void LoadAll();
	static void UnloadAll();

	static void FetchTexture(const path& pTexturePath);
	static Texture* LoadTexture(const std::string& pName);
	static Texture* GetTexture(const std::string& pName);
	static Animation GetAnimation(const std::vector<std::string>& pNames, float pFps = 60.0f);
	static Animation GetAnimation(const std::string& pName, int pStartFrame, int pEndFrame, float pFps = 60.0f);

	static void FetchShader(const path& pShaderPath);
	static Shader* LoadShader(const std::string& pName);
	static Shader* GetShader(const std::string& pName);
	
	static void FetchMesh(const path& pMeshPath);
	static Mesh* LoadMesh(const std::string& pName);
	static Mesh* GetMesh(const std::string& pName);

	static void FetchMaterial(const path& pMaterialPath);
	static Material* LoadMaterial(const std::string& pName);
	static Material* GetMaterial(const std::string& pName);

	static void FetchMap(const path& pMapPath);
	static Map* LoadMap(const std::string& pName);
	static Map* GetMap(const std::string& pName);
};