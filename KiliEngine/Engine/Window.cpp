#include "Window.h"
#include "Tools/Log.h"
#include "Config.h"

Window::Window():
	mSdlWindow( nullptr )
{
}

Vector2 Window::GetDimensions() const
{
	int width, height;
	SDL_GetWindowSize( mSdlWindow, &width, &height);
	return {width, height};
}

bool Window::Open()
{
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		Log::Error(LogType::Video, "Unable to initialize video");
	}
	else
	{
		Log::Info("Video initialized successfully");
	}

	Uint32 flags = SDL_WINDOW_OPENGL;

	switch (Cfg::WINDOW_MODE)
	{
		case ScreenMode::Fullscreen:
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
			break;

		case ScreenMode::Windowed:
			flags |= SDL_WINDOW_RESIZABLE;
			break;
	}

	if (Cfg::WINDOW_BORDERLESS)
	{
		flags |= SDL_WINDOW_BORDERLESS;
	}

	if (Cfg::WINDOW_ALWAYS_ON_TOP)
	{
		flags |= SDL_WINDOW_ALWAYS_ON_TOP;
	}
	
	mSdlWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Cfg::WINDOW_WIDTH, Cfg::WINDOW_HEIGHT, flags);

	if (!mSdlWindow)
	{
		Log::Error(LogType::System, "Failed to create window");
		return false;
	}
	else
	{
		Log::Info("Created Window successfully");
	}
	return true;
}

void Window::Close()
{
	SDL_DestroyWindow(mSdlWindow);
}
