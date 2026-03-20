#pragma once

#include "Texture.h"
#include "Mesh.h"
#include "Material.h"
#include <map>

#include <filesystem>
using std::filesystem::path;

#define TINYOBJLOADER_IMPLEMENTATION

enum AssetType : Uint8
{
	AssetTexture,
	AssetShader,
	AssetMesh,
	AssetMaterial,
};

class AssetManager
{
private:
	AssetManager() = default;

	static void SearchAFolderFor(const path& pFolderPath, AssetType pForWhat);
	
	static IRenderer* mRenderer;
	
	static std::map<std::string, Texture*> mLoadedTextures;
	static std::map<std::string, Shader*> mLoadedShaders;
	static std::map<std::string, Mesh*> mLoadedMeshes;
	static std::map<std::string, Material*> mLoadedMaterials;
	
	static std::map<std::string, path> mUnloadedTextures;
	static std::map<std::string, path> mUnloadedShaders;
	static std::map<std::string, path> mUnloadedMeshes;
	static std::map<std::string, path> mUnloadedMaterials;
	
	static Mesh* LoadMeshFromFile(const std::string& pFilePath);
	static Material* LoadMaterialFromFile(const std::string& pFilePath);
	
public:
	
	static void Init(IRenderer* pRenderer);
	static void Close();
	
	static void FetchAll();
	static void UnfetchAll();
	static void LoadAll();
	static void UnloadAll();

	static void FetchTexture(const path& pTexturePath);
	static Texture* LoadTexture(const std::string& pName);
	static Texture* GetTexture(const std::string& pName);

	static void FetchShader(const path& pShaderPath);
	static Shader* LoadShader(const std::string& pName);
	static Shader* GetShader(const std::string& pName);
	
	static void FetchMesh(const path& pMeshPath);
	static Mesh* LoadMesh(const std::string& pName);
	static Mesh* GetMesh(const std::string& pName);

	static void FetchMaterial(const path& pMaterialPath);
	static Material* LoadMaterial(const std::string& pName);
	static Material* GetMaterial(const std::string& pName);
};