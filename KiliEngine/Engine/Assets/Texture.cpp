#include "Texture.h"
#include "Engine/Renderer/OpenGlRenderer.h"
#include "Engine/Tools/Log.h"
#include "SDL_image.h"

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
	
	glGenerateMipmap(GL_TEXTURE_2D);
	
	SDL_FreeSurface(pSurface);
	Log::Info("Loaded Gl Texture : " + mFileName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // mip maps usage
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //u tiling
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //v tiling

	return true;
}

Texture::Texture() :
	mWidth(0), mHeight(0),
	mTextureId(0)
{
}

Texture::~Texture()
{
}

bool Texture::Load(GlRenderer* pRenderer, const std::string& pFilename)
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
	
	return LoadGl(pRenderer, goodFormatSurface);
}

void Texture::SetActive() const
{
	glBindTexture(GL_TEXTURE_2D, mTextureId);
}

bool Texture::Unload()
{
	glDeleteTextures(1, &mTextureId);
	mTextureId = 0;
	return true;
}

void Texture::UpdateInfo(int& w, int& h)
{
	w = mWidth;
	h = mHeight;
}
