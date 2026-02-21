#pragma once

#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"
#include <map>
#include <filesystem>

using std::filesystem::path;

enum AssetType : Uint8
{
	AssetTexture,
	AssetShader,
	AssetMesh,
};

class AssetManager
{
private:
	AssetManager() = default;

	static void SearchAFolderFor(const path& pFolderPath, AssetType pForWhat);
	
	static IRenderer* mRenderer;
	
	static std::map<std::string, Texture*> mLoadedTextures;
	static std::map<std::string, ShaderProgram*> mLoadedShaders;
	static std::map<std::string, Mesh*> mLoadedMeshes;
	
	static std::map<std::string, path> mUnloadedTextures;
	static std::map<std::string, path> mUnloadedShaders;
	static std::map<std::string, path> mUnloadedMeshes;
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
	static ShaderProgram* LoadShader(const std::string& pName);
	static ShaderProgram* GetShader(const std::string& pName);
	
	static void FetchMesh(const path& pMeshPath);
	static Mesh* LoadMesh(const std::string& pName);
	static Mesh* GetMesh(const std::string& pName);
};