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

	kStartScreen = new StartScreen();
}

GameManager::~GameManager()
{

	AudioManager::Release(); 
	kAudioManager = NULL; 

	AssetManager::Release(); 
	kAssetManager = NULL;

	Graphics::Release(); 
	kGraphics = NULL; 

	InputManager::Release(); 
	kInputManager = NULL;

	Timer::Release(); 
	kTimer = NULL; 

	delete kStartScreen;
	kStartScreen = NULL; 
}

void GameManager::EarlyUpdate()
{
	kInputManager->Update(); 
}

void GameManager::Update()
{	
	
	// Input
	// if (kInputManager->KeyDown(SDL_SCANCODE_W))
	// {

	// }

	kStartScreen->Update(); 
}

// Draw Calls
void GameManager::Render()
{
	kGraphics->ClearBackBuffer();

	kStartScreen->Render(); 

	// Render the current frame
	kGraphics->Render();
}

void GameManager::LateUpdate()
{
	kInputManager->UpdatePrevInput(); 
	kTimer->Reset(); 
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
			EarlyUpdate();
			Update(); 
			LateUpdate(); 
			Render(); 
		}
	}
}

