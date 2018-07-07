#include "ScreenManager.h"

ScreenManager* ScreenManager::sInstance = NULL;

ScreenManager* ScreenManager::Instance()
{
	if (sInstance == NULL)
		sInstance = new ScreenManager(); 
	return sInstance; 
}

void ScreenManager::Release()
{	
	delete sInstance; 
	sInstance = NULL;
}

ScreenManager::ScreenManager()
{	
	kInput = InputManager::Instance(); 
	kStars = BackgroundStars::Instance(); 
	kStartScreen = new StartScreen();
	kPlayScreen = new PlayScreen();
	kCurrentScreen = start; 
}

ScreenManager::~ScreenManager()
{
	kInput = NULL;

	BackgroundStars::Release(); 
	kStars = NULL; 

	delete kStartScreen;
	kStartScreen = NULL; 

	delete kPlayScreen;
	kPlayScreen = NULL; 
}

void ScreenManager::Update()
{
	kStars->Update(); 

	switch(kCurrentScreen)
	{
	case start: 
		kStartScreen->Update(); 
		if (kInput->KeyPressed(SDL_SCANCODE_RETURN))
		{
			kCurrentScreen = play;
			kStartScreen->ResetScroll(); 
			kPlayScreen->StartNewGame(); 
		}
		break;
	case play:
		kPlayScreen->Update(); 

		//NOTE(shaw): do we want to use a key besides escape? this is typically used to close the window.
		if (kInput->KeyPressed(SDL_SCANCODE_ESCAPE))
		{
			kCurrentScreen = start; 
		}
		break;
	}
}

void ScreenManager::Render()
{	
	kStars->Render(); 

	switch(kCurrentScreen)
	{
	case start: 
		kStartScreen->Render(); 
		break;
	case play: 
		kPlayScreen->Render(); 
		break;
	}
}
