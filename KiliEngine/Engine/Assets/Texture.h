#pragma once

#include "SDL.h"
#include <string>
#include <vector>

class GlRenderer;

class Texture
{

private:
	std::string mFileName;
	int	  mWidth, mHeight;
	unsigned int mTextureId;
	bool LoadGl(GlRenderer* pRenderer, SDL_Surface* pSurface);

public:
	Texture();
	~Texture();

	bool Unload();
	bool Load(GlRenderer* pRenderer, const std::string& pFilename);
	void SetActive() const;

	const std::string& GetFileName() const { return mFileName; }
	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }

	void UpdateInfo(int& pWOut, int& pHOut);
};

struct Animation
{
	std::vector<Texture*> Textures;
	float Fps;
};

