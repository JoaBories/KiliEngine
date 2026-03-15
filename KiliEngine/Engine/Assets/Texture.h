#pragma once

#include "SDL.h"
#include <string>

class IRenderer;
class SdlRenderer;
class GlRenderer;

class Texture
{

private:
	std::string mFileName;
	SDL_Texture* mSdlTexture;
	int	  mWidth, mHeight;
	unsigned int mTextureId;
	bool LoadSdl(SdlRenderer* pRenderer, SDL_Surface* pSurface);
	bool LoadGl(GlRenderer* pRenderer, SDL_Surface* pSurface);

public:
	Texture();
	~Texture();

	bool Unload();
	bool Load(IRenderer* pRenderer, const std::string& pFilename);
	void SetActive() const;

	const std::string& GetFileName() const { return mFileName; }
	SDL_Texture* GetTexture() const { return mSdlTexture; }
	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }

	void UpdateInfo(int& pWOut, int& pHOut);
};

