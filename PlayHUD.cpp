#include "PlayHUD.h"

PlayHUD::PlayHUD()
{
	kTimer = Timer::Instance(); 
	kAudio = AudioManager::Instance(); 

	kBackground = new Texture("black.png"); 
	kBackground->Parent(this); 
	kBackground->Pos(Vector2(30.0f, 70.0f));
	kBackground->Scale(Vector2(2.3f, 8.5f)); 

	// TODO(shaw): find a common location for colors
	SDL_Color desatRed = { 201, 31, 8 }; 

	kHighLabel = new Texture("HIGH", "emulogic.ttf", 24, desatRed); 
	kHighLabel->Parent(this); 
	kHighLabel->Pos(Vector2(0.0f, 0.0f));

	kScoreLabel = new Texture("SCORE", "emulogic.ttf", 24, desatRed); 
	kScoreLabel->Parent(this); 
	kScoreLabel->Pos(Vector2(40.0f, 24.0f));

	kHighScoreboard = new Scoreboard(); 
	kHighScoreboard->Parent(this); 
	kHighScoreboard->Pos(Vector2(88.0f, 48.0f));

	kPlayerOneLabel = new Texture("1UP", "emulogic.ttf", 24, desatRed); 
	kPlayerOneLabel->Parent(this);
	kPlayerOneLabel->Pos(Vector2(-7.0f, 120.0f));

	kBlinkTimer = 0.0f; 
	kBlinkInterval = 0.5f; 
	kPlayerOneLabelVisible = true; 

	kPlayerOneScore = new Scoreboard(); 
	kPlayerOneScore->Parent(this); 
	kPlayerOneScore->Pos(Vector2(88.0f, 144.0f));
}

PlayHUD::~PlayHUD()
{
	kTimer = NULL;
	kAudio = NULL;
	delete kBackground;
	kBackground = NULL; 
	delete kHighLabel;
	kHighLabel = NULL; 
	delete kScoreLabel;
	kScoreLabel = NULL; 
	delete kHighScoreboard;
	kHighScoreboard = NULL; 
	delete kPlayerOneLabel;
	kPlayerOneLabel = NULL; 
	delete kPlayerOneScore;
	kPlayerOneScore = NULL; 
}

void PlayHUD::SetHighScore(int score)
{
	kHighScoreboard->Score(score); 
}

void PlayHUD::SetPlayerScore(int score)
{
	kPlayerOneScore->Score(score); 
}

void PlayHUD::Update()
{
	kBlinkTimer += kTimer->DeltaTime(); 
	if (kBlinkTimer >= kBlinkInterval)
	{
		kPlayerOneLabelVisible = !kPlayerOneLabelVisible;
		kBlinkTimer = 0; 
	}
}

void PlayHUD::Render()
{
	kBackground->Render();
	kHighLabel->Render(); 
	kScoreLabel->Render(); 
	kHighScoreboard->Render(); 

	if (kPlayerOneLabelVisible)
		kPlayerOneLabel->Render(); 

	kPlayerOneScore->Render(); 
}