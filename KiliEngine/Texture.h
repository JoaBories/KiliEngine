#pragma once

#include "SDL.h"
#include <string>

class IRenderer;
class SdlRenderer;
class OpenGlRenderer;

class Texture
{

private:
	std::string mFileName;
	SDL_Texture* mSdlTexture;
	int	  mWidth, mHeight;
	bool LoadSdl(SdlRenderer* renderer, SDL_Surface* surface);
	bool LoadGl(OpenGlRenderer* renderer, SDL_Surface* surface);

public:

	Texture();
	~Texture();

	bool Load(IRenderer* renderer, const std::string& filename);
	bool Unload();
	void UpdateInfo(int& wOut, int& hOut);

	const std::string& GetFileName() const { return mFileName; };
	SDL_Texture* GetTexture() const { return mSdlTexture; };
	int GetWidth() const { return mWidth; };
	int GetHeight() const { return mHeight; };

};

