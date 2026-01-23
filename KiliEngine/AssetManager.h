#pragma once

#include "Texture.h"
#include "GameRenderer.h"
#include "SDL.h"
#include <map>

class AssetManager
{
public:
	//Storage for future References
	static std::map<std::string, Texture> mTextures;

	static Texture LoadTexture(GameRenderer& pRenderer, const std::string& pFileName, const std::string& pName);
	static Texture& GetTexture(const std::string& pName);
	static void Clear();

private:
	AssetManager() = default;
	static Texture LoadTextureFromFile(GameRenderer& pRenderer, const std::string& pFileName);
};