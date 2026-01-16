#include "Window.h"
#include "Log.h"

Window::Window(int pWidth, int pHeight):
	mSdlWindow( nullptr ),
	mDimensions( Vector2(pWidth, pHeight))
{
}

bool Window::Open()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		Log::Error(LogType::Video, "Unable to initialize video");
	}
	else
	{
		Log::Info("Video initialized successfully");
	}
	
	mSdlWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	static_cast<int>(mDimensions.x), static_cast<int>(mDimensions.y), SDL_WINDOW_OPENGL);

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
