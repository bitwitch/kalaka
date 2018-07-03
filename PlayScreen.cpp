#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	kTimer = Timer::Instance(); 
	kInput = InputManager::Instance(); 
	kStars = BackgroundStars::Instance(); 
	kPlayHUD = new PlayHUD(); 
	kPlayHUD->Parent(this); 
	kPlayHUD->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.85f, Graphics::Instance()->SCREEN_HEIGHT*0.05f));
	kPlayHUD->SetHighScore(30000); 
	kPlayHUD->SetPlayerScore(45000); 
}

PlayScreen::~PlayScreen()
{
	kTimer = NULL; 
	kInput = NULL; 
	kStars = NULL; 
	delete kPlayHUD;
	kPlayHUD = NULL;
}

void PlayScreen::Update()
{
	kPlayHUD->Update(); 
}

void PlayScreen::Render()
{
	kPlayHUD->Render(); 
}