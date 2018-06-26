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

	kAssetManager = AssetManager::Instance();

	kTex = new Texture("galaga_spritesheet.png", 182, 54, 22, 22); 

	kTex->Pos(Vector2(Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.5f)); 
}

GameManager::~GameManager()
{
	Graphics::Release(); 
	kGraphics = NULL; 

	Timer::Release(); 
	kTimer = NULL; 

	AssetManager::Release(); 
	kAssetManager = NULL;

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

