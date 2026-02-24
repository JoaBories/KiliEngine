#pragma once

#include <algorithm>
#include <SDL_timer.h>
#include "Log.h"

class GameTime
{

private:
	static constexpr unsigned int Fps = 120;
	static constexpr unsigned int FrameDelay = 1000/Fps;	//ms

	static unsigned int mFrameStart;						//ms
	static unsigned int mFrameTime;							//ms
	static unsigned int mLastFrame;							//ms

	static unsigned int mFrameCount;

public:
	GameTime() = default;
	~GameTime() = delete;
	GameTime(const GameTime&) = delete;
	GameTime& operator=(const GameTime&) = delete;
	GameTime(GameTime&& pOther) noexcept = delete;
	GameTime& operator=(GameTime&& pOther) noexcept = delete;

	static float DeltaTime;									//s

	static unsigned int ComputeDeltaTime() {
		mFrameStart = SDL_GetTicks();
		const unsigned int dt = mFrameStart - mLastFrame;
		mLastFrame = mFrameStart;
		DeltaTime = static_cast<float>(dt) / 1000.0f;
		mFrameCount++;
		return dt;
	}

	static void DelayTime() {
		mFrameTime = SDL_GetTicks() - mFrameStart;
		if (mFrameTime < FrameDelay)
			SDL_Delay(FrameDelay - mFrameTime);
	}

	static float GetAvgFrameTime() { return static_cast<float>(mFrameStart) / static_cast<float>(mFrameCount);}

};
