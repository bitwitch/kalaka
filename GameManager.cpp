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

	kAudioManager = AudioManager::Instance(); 

	kInputManager = InputManager::Instance(); 

	kScreenManager = ScreenManager::Instance(); 

}

GameManager::~GameManager()
{

	ScreenManager::Release(); 
	kScreenManager = NULL; 

	InputManager::Release(); 
	kInputManager = NULL; 

	AudioManager::Release(); 
	kAudioManager = NULL; 

	AssetManager::Release(); 
	kAssetManager = NULL;

	Graphics::Release(); 
	kGraphics = NULL; 

	Timer::Release(); 
	kTimer = NULL; 
}

void GameManager::EarlyUpdate()
{
	kInputManager->Update();
}

void GameManager::Update()
{	
	kScreenManager->Update(); 
}

// Draw Calls
void GameManager::Render()
{
	kGraphics->ClearBackBuffer();

	kScreenManager->Render(); 

	// Render the current frame
	kGraphics->Render();
}

void GameManager::LateUpdate()
{
	kTimer->Reset(); 
	kInputManager->UpdatePrevInput(); 
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

