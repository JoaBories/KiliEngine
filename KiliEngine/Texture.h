#pragma once

#include "SDL.h"
#include <string>

class SdlRenderer;

class Texture
{

private:
	std::string mFileName;
	SDL_Texture* mSdlTexture;
	int	  mWidth, mHeight;

public:

	Texture();
	~Texture();

	bool Load(SdlRenderer&, const std::string& filename);
	bool Unload();
	void UpdateInfo(int& wOut, int& hOut);

	const std::string& GetFileName() const { return mFileName; };
	SDL_Texture* GetTexture() const { return mSdlTexture; };
	int GetWidth() const { return mWidth; };
	int GetHeight() const { return mHeight; };

};

