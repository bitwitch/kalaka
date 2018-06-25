#include "Timer.h"

Timer* Timer::sInstance = NULL; 

Timer* Timer::Instance() 
{
	if (sInstance == NULL)
		sInstance = new Timer(); 
	return sInstance; 
}

void Timer::Release()
{
	delete sInstance; 
	sInstance = NULL; 
}

Timer::Timer()
{
	Reset(); 
	kTimeScale = 1.0f; 
}

Timer::~Timer()
{

}

void Timer::Reset()
{
	kStartTicks = SDL_GetTicks();
	kElapsedTicks = 0; 
	kDeltaTime = 0.0f; 
}

float Timer::DeltaTime()
{
	return kDeltaTime; 
}

void Timer::TimeScale(float t)
{
	kTimeScale = t; 
}

float Timer::TimeScale()
{
	return kTimeScale; 
}

void Timer::Update()
{
	kElapsedTicks = SDL_GetTicks() - kStartTicks; 
	kDeltaTime = kElapsedTicks * 0.001f; 
}
