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

	SDL_DestroyRenderer(kRenderer); 
	kRenderer = NULL;

	IMG_Quit(); 
	SDL_Quit(); 
}

bool Graphics::Init()
{	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		printf("SDL Initialization Error: %s\n", SDL_GetError()); 
		return false;
	}
	
	kWindow = SDL_CreateWindow("Kalaka", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); 
	if (kWindow == NULL)
	{
		printf("Window Creation Error: %s\n", SDL_GetError()); 
		return false; 
	}

	kRenderer = SDL_CreateRenderer(kWindow, -1, SDL_RENDERER_ACCELERATED); 
	if (kRenderer == NULL)
	{
		printf("Renderer Creation Error: %s\n", SDL_GetError()); 
		return false; 
	}

	SDL_SetRenderDrawColor(kRenderer, 0xFF, 0xFF, 0xFF, 0xFF); 

	int flags = IMG_INIT_PNG; 
	if (!(IMG_Init(flags) & flags))
	{
		printf("Image Initialization Error: %s\n", IMG_GetError()); 
		return false; 
	}

	kBackBuffer = SDL_GetWindowSurface(kWindow);
	return true; 
}

SDL_Texture* Graphics::LoadTexture(std::string path)
{
	SDL_Texture* tex = NULL; 

	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == NULL)
	{
		printf("Image Load Error: Path(%s) - Error(%s)\n", path.c_str(), IMG_GetError()); 
		return tex; 
	}

	tex = SDL_CreateTextureFromSurface(kRenderer, surface); 
	if (tex == NULL)
	{
		printf("Create Texture Error: Error(%s)\n", SDL_GetError()); 
		return tex; 
	}

	SDL_FreeSurface(surface); 

	return tex; 
}

void Graphics::ClearBackBuffer()
{
	SDL_RenderClear(kRenderer); 
}

void Graphics::DrawTexture(SDL_Texture* tex, SDL_Rect* clip, SDL_Rect* rend)
{
	SDL_RenderCopy(kRenderer, tex, clip, rend); 
}

void Graphics::Render()
{
	SDL_RenderPresent(kRenderer); 
}
