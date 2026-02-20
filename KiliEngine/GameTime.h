#pragma once

#include <algorithm>
#include <SDL_timer.h>
#include "Log.h"

class GameTime
{

public:
	GameTime() = default;
	~GameTime() = delete;
	GameTime(const GameTime&) = delete;
	GameTime& operator=(const GameTime&) = delete;
	GameTime(GameTime&& pOther) noexcept = delete;
	GameTime& operator=(GameTime&& pOther) noexcept = delete;

	static unsigned int ComputeDeltaTime() {
		mFrameStart = SDL_GetTicks();
		unsigned int dt = mFrameStart - mLastFrame;
		mLastFrame = mFrameStart;
		dt = std::min(dt, MaxDt);
		DeltaTime = static_cast<float>(dt) / 1000.0f;
		return dt;
	}

	static void DelayTime() {
		mFrameTime = SDL_GetTicks() - mFrameStart;
		if (mFrameTime < FrameDelay)
			SDL_Delay(FrameDelay - mFrameTime);
	}

	static float DeltaTime;

private:
	static constexpr unsigned int Fps = 60;
	static constexpr unsigned int FrameDelay = 1000/Fps;

	static constexpr unsigned int MaxDt = 50;

	static unsigned int mFrameStart;
	static unsigned int mFrameTime;
	static unsigned int mLastFrame;
};