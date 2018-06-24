#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <SDL2/sdl.h>
#include <stdio.h>

class Graphics 
{
public:
	static const int SCREEN_WIDTH  = 1080; 
	static const int SCREEN_HEIGHT = 720; 

private: 
	static Graphics* sInstance;
	static bool sInitialized;

	SDL_Window* kWindow;
	SDL_Surface* kBackBuffer; 

public: 
	static Graphics* Instance();
	static void Release(); 
	static bool Initialized(); 

	void Render(); 

private: 
	Graphics(); 
	~Graphics(); 

	bool Init(); 
};

#endif
