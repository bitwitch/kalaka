#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	kTimer = Timer::Instance(); 
	kInput = InputManager::Instance(); 
	kStars = BackgroundStars::Instance(); 
	kAudio = AudioManager::Instance(); 

	kHUD = new PlayHUD(); 
	kHUD->Parent(this); 
	kHUD->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.85f, Graphics::Instance()->SCREEN_HEIGHT*0.05f));

	// TODO(shaw): find a common loc to store colors
	SDL_Color desatRed = { 201, 31, 8 }; 
	kStartLabel = new Texture("START", "emulogic.ttf", 24, desatRed); 
	kStartLabel->Parent(this);
	kStartLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.37f, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

	kLevel = NULL; 

	kLevelStartDelay = 1.0f; 
	kLevelStarted = false; 
}

PlayScreen::~PlayScreen()
{
	kTimer = NULL; 
	kInput = NULL; 
	kAudio = NULL; 
	kStars = NULL; 
	delete kHUD;
	kHUD = NULL;
	delete kStartLabel; 
	kStartLabel = NULL; 
	delete kLevel; 
	kLevel = NULL; 
}

void PlayScreen::StartNewGame()
{
	kStars->Scroll(false); 
	kHUD->SetHighScore(30000); // TODO(shaw): change once we have game saving
	kHUD->SetShips(2); 
	kGameStarted = false;
	kAudio->PlayMusic("startlevel.wav", 0); 
	kCurrentStage = 105;
}

void PlayScreen::StartNextLevel()
{
	kCurrentStage++;
	kLevelStartTimer = 0.0f; 
	kLevelStarted = true;
	delete kLevel; 
	kLevel = new Level(kCurrentStage, kHUD);
}

void PlayScreen::Update()
{	
	if (kGameStarted)
	{
		if (kLevelStarted)
		{
			kHUD->Update(); 
			kLevel->Update();
		}
		else 
		{
			kLevelStartTimer += kTimer->DeltaTime(); 
			if (kLevelStartTimer >= kLevelStartDelay)
				StartNextLevel();
		}
	}
	else 
	{
		if (!Mix_PlayingMusic())
			kGameStarted = true; 
	}
}

void PlayScreen::Render()
{
	kHUD->Render(); 

	if (!kGameStarted)
		kStartLabel->Render(); 
	
	if (kGameStarted && kLevelStarted)
		kLevel->Render();
}