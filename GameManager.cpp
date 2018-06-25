#include "GameManager.h"

GameManager* GameManager::sInstance = NULL; 

GameManager* GameManager::Instance()
{
	if (sInstance == NULL)
		sInstance = new GameManager();
	return sInstance;
}

void GameManager::Release()
{
	delete sInstance; 
	sInstance = NULL; 
}

GameManager::GameManager()
{
	kQuit     = false; 
	kGraphics = Graphics::Instance();

	if (!Graphics::Initialized())
		kQuit = true; 

	kTimer = Timer::Instance(); 

	std::string path = SDL_GetBasePath();
	path.append("assets/galaga_spritesheet.png"); 
	kTex = new Texture(path); 
}

GameManager::~GameManager()
{
	Graphics::Release(); 
	kGraphics = NULL; 

	Timer::Release(); 
	kTimer = NULL; 

	delete kTex; 
	kTex = NULL; 
}

void GameManager::Run()
{
	while (!kQuit)
	{
		kTimer->Update();

		while (SDL_PollEvent(&kEvents) != 0)
		{
			if (kEvents.type == SDL_QUIT)
				kQuit = true;

			// handle other events

		}

		// only update during framerate 
		if (kTimer->DeltaTime() >= (1.0f / FRAME_RATE) )
		{	
			kGraphics->ClearBackBuffer();

			// DRAW CALLS 
			kTex->Render(); 

			kGraphics->Render(); 
			kTimer->Reset(); 
		}
	}
}

