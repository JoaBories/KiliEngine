#pragma once

#include <SDL_timer.h>
#include "Log.h"
#include "Engine/Config.h"


class GameTime
{

private:
	
	static Uint64 mFrameStart;							//tick
	static Uint64 mFrameTime;							//tick
	static Uint64 mLastFrame;							//tick
	
	static const Uint64 Frequency;						//hertz tick per second
	static const Uint64 TicksPerFrame;
	
	static Uint64 mTotalTime;							//tick
	static Uint64 mFrameCount;

public:
	GameTime() = default;
	~GameTime() = delete;
	GameTime(const GameTime&) = delete;
	GameTime& operator=(const GameTime&) = delete;
	GameTime(GameTime&& pOther) noexcept = delete;
	GameTime& operator=(GameTime&& pOther) noexcept = delete;

	static float DeltaTime;								//s

	static void Init()
	{
		//mFrequency = SDL_GetPerformanceFrequency();
		Log::Info(std::to_string(Frequency));
		mLastFrame = SDL_GetPerformanceCounter();
		mFrameStart = mLastFrame;
	}

	static Uint64 ComputeDeltaTime() {
		mFrameStart = SDL_GetPerformanceCounter();
		const Uint64 dt = mFrameStart - mLastFrame;
		mLastFrame = mFrameStart;
		DeltaTime = static_cast<float>(dt) / static_cast<float>(Frequency);
		mTotalTime += dt;
		mFrameCount++;
		return dt;
	}

	static void DelayTime() {
		if constexpr (Cfg::FPS_LOCKED != Limited) return;

		const Uint64 elapsed = SDL_GetPerformanceCounter() - mFrameStart;

		if (elapsed < TicksPerFrame) {
			const Uint32 ms = static_cast<Uint32>((TicksPerFrame - elapsed) / Frequency * 1000);
			
			if (ms > 0) SDL_Delay(ms); // Wait in ms
			while (SDL_GetPerformanceCounter() - mFrameStart < TicksPerFrame) {} // Wait precisely the rest (this function busy the core)
		}
	}

	static double GetAvgFrameTime()
	{
		if (mFrameCount == 0) return 0.0;
		return static_cast<double>(mTotalTime) / static_cast<double>(Frequency) / static_cast<double>(mFrameCount) * 1000.0;
	}

};
