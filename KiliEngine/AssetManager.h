#pragma once

#include "Texture.h"
#include "Shader.h"
#include <map>

const std::string TexturePath = "Resources/";
const std::string ShaderPath = "Resources/Shaders/";

class AssetManager
{
private:
	AssetManager() = default;
	
public:
	//Storage for future References
	static std::map<std::string, Texture*> Textures;
	static std::map<std::string, ShaderProgram*> Shaders;

	static Texture* LoadTexture(IRenderer* pRenderer, const std::string& pFileName, const std::string& pName);
	static Texture* GetTexture(const std::string& pName);

	static ShaderProgram* LoadShader(const std::string& pName);
	static ShaderProgram* GetShader(const std::string& pName);

	static void Clear();
};