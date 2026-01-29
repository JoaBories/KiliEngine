#include "Texture.h"
#include "SdlRenderer.h"
#include "OpenGlRenderer.h"
#include "Log.h"

bool Texture::LoadSdl(SdlRenderer* renderer, SDL_Surface* surface)
{
	mSdlTexture = SDL_CreateTextureFromSurface(renderer->GetSdlRenderer(), surface);
	SDL_FreeSurface(surface);
	if (!mSdlTexture)
	{
		Log::Error(LogType::Render, "Failed to convert surface to texture :" + mFileName);
		return false;
	}
	Log::Info("Loaded texture : " + mFileName);
	return true;
}

bool Texture::LoadGl(OpenGlRenderer* renderer, SDL_Surface* surface)
{
	return false;
}

Texture::Texture() :
	mFileName(),
	mSdlTexture(nullptr),
	mWidth(0), mHeight(0)
{
}

Texture::~Texture()
{
}

bool Texture::Load(IRenderer* renderer, const std::string& filename)
{
	mFileName = filename;
	SDL_Surface* surface = IMG_Load(mFileName.c_str());
	if (!surface)
	{
		Log::Error(LogType::Application, "Failed to load texture file :" + mFileName);
		return false;
	}
	mWidth = surface->w;
	mHeight = surface->h;

	if (renderer->GetType() == SDL)
	{
		return LoadSdl(static_cast<SdlRenderer*>(renderer), surface);
	}
	else
	{
		return LoadGl(static_cast<OpenGlRenderer*>(renderer), surface);
	}
	
	return true;
}

bool Texture::Unload()
{
	if (mSdlTexture)
	{
		SDL_DestroyTexture(mSdlTexture);
		mSdlTexture = nullptr;
		return true;
	}
	return false;
}

void Texture::UpdateInfo(int& w, int& h)
{
	w = mWidth;
	h = mHeight;
}
