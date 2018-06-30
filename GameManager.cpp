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

	kInputManager = InputManager::Instance(); 

	// kTex = new Texture("galaga_spritesheet.png", 184, 55, 14, 15);
	kTex = new AnimatedTexture("galaga_spritesheet.png", 204, 45, 40, 38, 4, 1.5f, AnimatedTexture::horizontal);
	kTex->WrapMode(AnimatedTexture::once); 
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

	InputManager::Release(); 
	kInputManager = NULL;

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
			// Input
			kInputManager->Update(); 

			if (kInputManager->KeyDown(SDL_SCANCODE_W))
			{
				kTex->Translate(Vector2(0.0f, -40.0f) * kTimer->DeltaTime());
			}
			else if (kInputManager->KeyDown(SDL_SCANCODE_A))
			{
				kTex->Translate(Vector2(-40.0f, 0.0f) * kTimer->DeltaTime());
			}
			else if (kInputManager->KeyDown(SDL_SCANCODE_S))
			{
				kTex->Translate(Vector2(0.0f, 40.0f) * kTimer->DeltaTime());
			}
			else if (kInputManager->KeyDown(SDL_SCANCODE_D))
			{
				kTex->Translate(Vector2(40.0f, 0.0f) * kTimer->DeltaTime());
			}

			// Texure update
			kTex->Update(); 

			kGraphics->ClearBackBuffer();

			// DRAW CALLS 
			kTex->Render(); 

			kGraphics->Render(); 
			kTimer->Reset(); 
		}
	}
}

