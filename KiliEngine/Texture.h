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
	bool LoadSdl(SdlRenderer* renderer, SDL_Surface* surface);
	bool LoadGl(GlRenderer* renderer, SDL_Surface* surface);

public:
	Texture();
	~Texture();

	bool Unload();
	bool Load(IRenderer* renderer, const std::string& filename);
	void SetActive() const;

	const std::string& GetFileName() const { return mFileName; };
	inline SDL_Texture* GetTexture() const { return mSdlTexture; };
	int GetWidth() const { return mWidth; };
	int GetHeight() const { return mHeight; };

	void UpdateInfo(int& wOut, int& hOut);
};

