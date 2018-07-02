#include "GameManager.h"
#include <time.h>

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
	srand(time(0));
	
	kQuit     = false; 
	kGraphics = Graphics::Instance();

	if (!Graphics::Initialized())
		kQuit = true; 

	
	kTimer = Timer::Instance(); 

	kAssetManager = AssetManager::Instance();

	kInputManager = InputManager::Instance(); 

	kAudioManager = AudioManager::Instance(); 

	kStars = BackgroundStars::Instance(); 

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

	BackgroundStars::Release(); 
	kStars = NULL; 

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

	kStars->Update();

	kStartScreen->Update(); 
}

// Draw Calls
void GameManager::Render()
{
	kGraphics->ClearBackBuffer();

	kStars->Render();

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

