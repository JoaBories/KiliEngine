#pragma once

#include <SDL.h>
#include <string>
#include <SDL_error.h>

enum class LogType
{
	Application = SDL_LOG_CATEGORY_APPLICATION,
	Assert = SDL_LOG_CATEGORY_ASSERT,
	Audio = SDL_LOG_CATEGORY_AUDIO,
	Error = SDL_LOG_CATEGORY_ERROR,
	Input = SDL_LOG_CATEGORY_INPUT,
	Render = SDL_LOG_CATEGORY_RENDER,
	System = SDL_LOG_CATEGORY_SYSTEM,
	Test = SDL_LOG_CATEGORY_TEST,
	Video = SDL_LOG_CATEGORY_VIDEO
};


class Log
{
public:
	Log() = delete;
	Log(const Log&) = delete;
	Log& operator=(const Log&) = delete;

	inline static void Info(const std::string& message) { 
		SDL_Log((message + "\n").c_str());
	};

	inline static void Error(LogType category, const std::string& message) { 
		SDL_LogError(static_cast<int>(category), "%s | SDL : %s", message.c_str(), SDL_GetError());
	};
};

