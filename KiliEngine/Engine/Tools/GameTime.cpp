#include "GameTime.h"

Uint64 GameTime::mFrameStart = 0;
Uint64 GameTime::mFrameTime = 0;
Uint64 GameTime::mLastFrame = 0;

const Uint64 GameTime::Frequency = SDL_GetPerformanceFrequency();
const Uint64 GameTime::TicksPerFrame = Frequency / Cfg::FPS_MAX;

Uint64 GameTime::mTotalTime = 0;
Uint64 GameTime::mFrameCount = 0;

float GameTime::DeltaTime = 0;
