#include "Graphics.h"

Graphics* Graphics::sInstance = NULL; 
bool Graphics::sInitialized = false; 

Graphics* Graphics::Instance() 
{
	if (sInstance == NULL) 
		sInstance = new Graphics(); 
	return sInstance; 
}


void Graphics::Release() 
{
	delete sInstance; 
	sInstance = NULL;
	sInitialized = false; 
}

bool Graphics::Initialized() 
{
	return sInstance;
}

Graphics::Graphics() 
{
	kBackBuffer = NULL;
	sInitialized = Init();
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(kWindow); 
	kWindow = NULL; 
	SDL_Quit(); 
}

bool Graphics::Init()
{	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		printf("SDL Initialization Error: %s\n", SDL_GetError); 
		return false;
	}
	
	kWindow = SDL_CreateWindow("Kalaka", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); 

	if (kWindow == NULL)
	{
		printf("Window Creation Error: %s\n", SDL_GetError); 
		return false; 
	}

	kBackBuffer = SDL_GetWindowSurface(kWindow);
	return true; 
}

void Graphics::Render()
{
	SDL_UpdateWindowSurface(kWindow); 
}
