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

	kAudioManager = AudioManager::Instance(); 

	// kTexEvil = new Texture("galaga_spritesheet.png", 184, 55, 14, 15);
	// kTex = new AnimatedTexture("galaga_spritesheet.png", 204, 45, 40, 38, 4, 1.5f, AnimatedTexture::horizontal);
	// kTex->WrapMode(AnimatedTexture::once); 

	SDL_Color tan = {190,145,100}; 
	kTex = new Texture("Kalaka", "ARCADE.otf", 100, tan);

	kTex->Pos(Vector2(Graphics::SCREEN_WIDTH*0.5f, 100)); 

}

GameManager::~GameManager()
{

	AudioManager::Release(); 
	kAudioManager = NULL; 

	AssetManager::Release(); 
	kAssetManager = NULL;

	Graphics::Release(); 
	kGraphics = NULL; 

	Timer::Release(); 
	kTimer = NULL; 

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
			else if (kInputManager->KeyDown(SDL_SCANCODE_P))
			{
				kAudioManager->PlaySFX("jump4.wav");
			}
			
			kGraphics->ClearBackBuffer();

			// DRAW CALLS 
			kTex->Render(); 	

			kGraphics->Render(); 
			kTimer->Reset(); 
		}
	}
}

