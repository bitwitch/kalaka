#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string>
#include <stdio.h>

class Graphics 
{
public:

	static const int SCREEN_WIDTH  = 1080; 
	static const int SCREEN_HEIGHT = 720; 

private: 

	static Graphics* sInstance;
	static bool sInitialized;

	SDL_Window*   kWindow;
	SDL_Surface*  kBackBuffer; 
	SDL_Renderer* kRenderer; 

public: 

	static Graphics* Instance();
	static void Release(); 
	static bool Initialized(); 

	SDL_Texture* LoadTexture(std::string path); 
	void ClearBackBuffer();
	void DrawTexture(SDL_Texture* tex, SDL_Rect* clip = NULL, SDL_Rect* rend = NULL); 
	void Render(); 

private: 

	Graphics(); 
	~Graphics(); 

	bool Init(); 
};

#endif
