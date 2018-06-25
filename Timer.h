#ifndef _TIMER_H
#define _TIMER_H

#include <SDL2/sdl.h> 

class Timer 
{
private:

	static Timer* sInstance; 
	unsigned int kStartTicks;
	unsigned int kElapsedTicks; 
	float kDeltaTime; 
	float kTimeScale;

public: 

	static Timer* Instance();
	static void Release();

	void Reset(); 
	float DeltaTime(); 
	void TimeScale(float t); 
	float TimeScale(); 
	void Update(); 

private: 

	Timer(); 
	~Timer();
}; 

#endif