#pragma once

#include <algorithm>
#include <SDL_timer.h>

class Time
{

public:
	Time() = default;
	Time(const Time&) = delete;
	Time& operator=(const Time&) = delete;

	inline static unsigned int ComputeDeltaTime() {
		mFrameStart = SDL_GetTicks();
		unsigned int dt = mFrameStart - mLastFrame;
		mLastFrame = mFrameStart;
		dt = std::min(dt, MAX_DT);
		deltaTime = dt / 1000.0f;
		return dt;
	};

	inline static void DelayTime() {
		mFrameTime = SDL_GetTicks() - mFrameStart;
		if (mFrameTime < FrameDelay)
			SDL_Delay(FrameDelay - mFrameTime);
	};

	static float deltaTime;

private:
	const static unsigned int FPS = 60;
	const static unsigned int FrameDelay = 1000/FPS;

	const static unsigned int MAX_DT = 50;

	static unsigned int mFrameStart;
	static unsigned int mFrameTime;
	static unsigned int mLastFrame;
};