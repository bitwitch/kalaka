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
	kTimer    = Timer::Instance(); 

	if (!Graphics::Initialized())
		kQuit = true; 
}

GameManager::~GameManager()
{
	Graphics::Release(); 
	kGraphics = NULL; 

	Timer::Release(); 
	kTimer = NULL; 
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
			printf("DeltaTime: %F\n", kTimer->DeltaTime()); 
			kGraphics->Render(); 
			kTimer->Reset(); 
		}
	}
}

