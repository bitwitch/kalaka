#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <string>
#include <stdio.h>

class Graphics 
{
public:

	static const int SCREEN_WIDTH   = 968; 
	static const int SCREEN_HEIGHT  = 847;
	const char* WINDOW_TITLE = "Kalaka";

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

	SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color);

	void ClearBackBuffer();
	void DrawTexture(SDL_Texture* tex, SDL_Rect* clip = NULL, SDL_Rect* rend = NULL, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE); 
	void Render(); 

private: 

	Graphics(); 
	~Graphics(); 

	bool Init(); 
};

#endif
