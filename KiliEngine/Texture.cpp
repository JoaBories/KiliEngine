#include "Texture.h"
#include "SdlRenderer.h"
#include "OpenGlRenderer.h"
#include "Log.h"

bool Texture::LoadSdl(SdlRenderer* pRenderer, SDL_Surface* pSurface)
{
	mSdlTexture = SDL_CreateTextureFromSurface(pRenderer->GetSdlRenderer(), pSurface);
	if (!mSdlTexture)
	{
		Log::Error(LogType::Render, "Failed to convert surface to texture :" + mFileName);
		return false;
	}
	Log::Info("Loaded texture : " + mFileName);
	return true;
}

bool Texture::LoadGl(GlRenderer* pRenderer, SDL_Surface* pSurface)
{
	int format = 0;
	if (pSurface->format->format == SDL_PIXELFORMAT_RGB24)
	{
		format = GL_RGB;
	}
	else if (pSurface->format->format == SDL_PIXELFORMAT_RGBA32)
	{
		format = GL_RGBA;
	}
	glGenTextures(1, &mTextureId);
	glBindTexture(GL_TEXTURE_2D, mTextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, pSurface->pixels);
	SDL_FreeSurface(pSurface);
	Log::Info("Loaded Gl Texture : " + mFileName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;
}

Texture::Texture() :
	mFileName(),
	mSdlTexture(nullptr),
	mWidth(0), mHeight(0),
	mTextureId(0)
{
}

Texture::~Texture()
{
}

bool Texture::Load(IRenderer* pRenderer, const std::string& pFilename)
{
	mFileName = pFilename;
	SDL_Surface* surface = IMG_Load(mFileName.c_str());
	SDL_Surface* goodFormatSurface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
	if (!surface)
	{
		Log::Error(LogType::Application, "Failed to load texture file :" + mFileName);
		return false;
	}
	mWidth = surface->w;
	mHeight = surface->h;

	if (pRenderer->GetType() == Sdl)
	{
		return LoadSdl(dynamic_cast<SdlRenderer*>(pRenderer), surface);
	}
	else
	{
		return LoadGl(dynamic_cast<GlRenderer*>(pRenderer), surface);
	}

	SDL_FreeSurface(surface);
	SDL_FreeSurface(goodFormatSurface);
	
	return true;
}

void Texture::SetActive() const
{
	glBindTexture(GL_TEXTURE_2D, mTextureId);
}

bool Texture::Unload()
{
	if (mSdlTexture)
	{
		SDL_DestroyTexture(mSdlTexture);
		mSdlTexture = nullptr;
		return true;
	}
	else
	{
		glDeleteTextures(1, &mTextureId);
		mTextureId = 0;
		return true;
	}
	return false;
}

void Texture::UpdateInfo(int& w, int& h)
{
	w = mWidth;
	h = mHeight;
}
