#pragma once

#include "Texture.h"
#include "Shader.h"
#include "IRenderer.h"
#include "SDL.h"
#include <map>

class AssetManager
{
public:
	//Storage for future References
	static std::map<std::string, Texture*> mTextures;
	static std::map<std::string, ShaderProgram*> mShaders;

	static Texture* LoadTexture(IRenderer* pRenderer, const std::string& pFileName, const std::string& pName);
	static Texture* GetTexture(const std::string& pName);

	static ShaderProgram* LoadShader(const std::string& pName);
	static ShaderProgram* GetShader(const std::string& pName);

	static void Clear();

private:
	AssetManager() = default;
	static Texture* LoadTextureFromFile(IRenderer* pRenderer, const std::string& pFileName);
};