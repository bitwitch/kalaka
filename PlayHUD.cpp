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

	// Scoreboard
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

	// Player Lives
	kShips = new GameEntity();
	kShips->Parent(this); 
	kShips->Pos(Vector2(-33.0f, 400.0f)); 

	for (int i=0; i<MAX_SHIP_TEXTURES; i++)
	{
		kShipTextures[i] = new Texture("galaga_spritesheet.png", 185, 56, 15, 16); 
		kShipTextures[i]->Parent(kShips); 
		kShipTextures[i]->Scale(4.0f); 
		kShipTextures[i]->Pos(Vector2(63.0f * (i % 3), 67.0f * (i / 3) )); 
	}

	kTotalShipsLabel = new Scoreboard(); 
	kTotalShipsLabel->Parent(kShips); 
	kTotalShipsLabel->Pos(Vector2(137.0f, 75.f)); 

	// Level Flags
	kFlags = new GameEntity(); 
	kFlags->Parent(this);
	kFlags->Pos(Vector2(-49.0f, 600.0f));

	kFlagTimer = 0.0f; 
	kFlagInterval = 0.25f;
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
	delete kShips;
	kShips = NULL; 

	for (int i=0; i<MAX_SHIP_TEXTURES; i++)
	{
		delete kShipTextures[i];
		kShipTextures[i] = NULL;
	}

	delete kTotalShipsLabel;
	kTotalShipsLabel = NULL; 

	delete kFlags;
	kFlags = NULL; 
	ClearFlags(); 
}

void PlayHUD::ClearFlags()
{
	for (int i=0; i<kFlagTextures.size(); i++)
	{
		delete kFlagTextures[i]; 
		kFlagTextures[i] = NULL;
	}
	kFlagTextures.clear(); 
}

void PlayHUD::AddNextFlag()
{	
	if (kRemainingLevels >= 50)
		AddFlag("galaga_spritesheet.png", 265, 288, 15, 16, 50);
	else if (kRemainingLevels >= 30)
		AddFlag("galaga_spritesheet.png", 289, 288, 15, 16, 30);
	else if (kRemainingLevels >= 20)
		AddFlag("galaga_spritesheet.png", 313, 288, 15, 16, 20);
	else if (kRemainingLevels >= 10)
		AddFlag("galaga_spritesheet.png", 338, 290, 13, 14, 10);
	else if (kRemainingLevels >= 5)
		AddFlag("galaga_spritesheet.png", 361, 290, 7, 14, 5);
	else
		AddFlag("galaga_spritesheet.png", 377, 292, 7, 12, 1);
}

void PlayHUD::AddFlag(std::string filename, int x, int y, int w, int h, int value)
{	
	int index = kFlagTextures.size(); 
	float scale = 4.0f; 
	
	if (index > 0)
		kFlagXOffset += (w * scale * 0.5f) + 2.0f; 
	
	kRemainingLevels -= value; 
	kFlagTextures.push_back(new Texture(filename, x, y, w, h));
	kFlagTextures[index]->Parent(kFlags); 
	kFlagTextures[index]->Scale(scale);
	kFlagTextures[index]->Pos(VEC2_RIGHT*kFlagXOffset); 
	kFlagXOffset += (w * scale * 0.5f) + 2.0f; 

	kAudio->PlaySFX("flagsound.wav");
}

void PlayHUD::SetHighScore(int score)
{
	kHighScoreboard->Score(score); 
}

void PlayHUD::SetPlayerScore(int score)
{
	kPlayerOneScore->Score(score); 
}

void PlayHUD::SetShips(int ships)
{
	kTotalShips = ships; 
	if (ships > MAX_SHIP_TEXTURES)
		kTotalShipsLabel->Score(ships);
}

void PlayHUD::SetLevel(int level)
{
	ClearFlags(); 
	kRemainingLevels = level;
	kFlagXOffset = 0.0f; 
}

void PlayHUD::Update()
{
	kBlinkTimer += kTimer->DeltaTime(); 
	if (kBlinkTimer >= kBlinkInterval)
	{
		kPlayerOneLabelVisible = !kPlayerOneLabelVisible;
		kBlinkTimer = 0; 
	}

	if (kRemainingLevels > 0)
	{
		kFlagTimer += kTimer->DeltaTime();
		if (kFlagTimer >= kFlagInterval)
		{
			AddNextFlag(); 
			kFlagTimer = 0.0f; 
		}
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

	for (int i=0; i<MAX_SHIP_TEXTURES && i < kTotalShips; i++)
		kShipTextures[i]->Render();
	
	if (kTotalShips > MAX_SHIP_TEXTURES)
		kTotalShipsLabel->Render(); 

	for (int i=0; i<kFlagTextures.size(); i++)
		kFlagTextures[i]->Render(); 
	
}