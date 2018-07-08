#include "Level.h"

Level::Level(int stage, PlayHUD* hud, Player* player)
{
	kTimer = Timer::Instance(); 
	kHUD = hud; 
	kHUD->SetLevel(stage); 
	kStars = BackgroundStars::Instance(); 

	kStage = stage; 
	kStageStarted = false; 

	kLabelTimer = 0.0f; 

	// Colors TODO(shaw): colors in single loc
	SDL_Color lightBlue = { 75, 75, 200 };
	SDL_Color desatRed = { 201, 31, 8 }; 

	kStageLabel = new Texture("STAGE", "emulogic.ttf", 24, lightBlue); 
	kStageLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.33f, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

	kStageNumber = new Scoreboard(lightBlue);

	kStageNumber->Score(kStage); 
	kStageNumber->Parent(this); 
	kStageNumber->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.45f, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

	kStageLabelOnScreen = 0.0f; 

	// kStageLabelOffScreen = 1.5f;
	//NOTE(shaw): DEBUGGING 
	kStageLabelOffScreen = 0.1f;
	
	kReadyLabel = new Texture("READY", "emulogic.ttf", 24, desatRed); 
	kReadyLabel->Parent(this);
	kReadyLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.38f, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

	kReadyLabelOnScreen = kStageLabelOffScreen;

	// kReadyLabelOffScreen = kReadyLabelOnScreen + 3.0f;
	//NOTE(shaw): DEBUGGING 
	kReadyLabelOffScreen = 0.1f;

	kPlayer = player;
	
	kPlayerHit = false; 

	// kPlayerRespawnDelay = 3.0f; 
	//NOTE(shaw): DEBUGGING 
	kPlayerRespawnDelay = 0.1f;

	kPlayerRespawnTimer = 0.0f; 

	// kPlayerRespawnLabelOnScreen = 2.0f;
	//NOTE(shaw): DEBUGGING 
	kPlayerRespawnLabelOnScreen = 0.1f;

	kGameOverLabel = new Texture("GAME OVER", "emulogic.ttf", 24, desatRed); 
	kGameOverLabel->Parent(this);
	kGameOverLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.38f, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

	kGameOver = false; 
	kGameOverDelay = 6.0f;
	kGameOverTimer = 0.0f; 
	kGameOverLabelOnScreen = 1.0f;

	kCurrentState = running; 

	kEnemy = new Enemy(0); 
}

Level::~Level()
{
	kTimer = NULL; 
	kHUD = NULL; 
	kStars = NULL; 
	kPlayer = NULL; 
	delete kStageLabel;
	kStageLabel = NULL; 
	delete kStageNumber;
	kStageNumber = NULL; 
	delete kReadyLabel;
	kReadyLabel = NULL; 
	delete kGameOverLabel;
	kGameOverLabel = NULL; 

	delete kEnemy;
	kEnemy = NULL; 
}

void Level::StartStage()
{	
	// TODO(shaw): spawn shit
	kStageStarted = true; 
}

void Level::HandleStartLabels()
{
	kLabelTimer += kTimer->DeltaTime(); 
		if (kLabelTimer >= kStageLabelOffScreen)
		{
			kStars->Scroll(true);

			if (kStage > 1)
				StartStage();
			else if (kLabelTimer >= kReadyLabelOffScreen)
			{
				StartStage();
				kPlayer->Active(true); 
				kPlayer->Visible(true); 
			}
		}
}

void Level::HandleCollisions()
{
	if (!kPlayerHit)
	{
		// TODO(shaw): implement collisions and replace the button press here
		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_X))
		{
			kPlayer->WasHit();
			kHUD->SetShips(kPlayer->Lives());
			kPlayerHit = true; 
			kPlayerRespawnTimer = 0.0f; 
			kPlayer->Active(false); 
			kStars->Scroll(false);
		}
	}
}

void Level::HandlePlayerDeath()
{
	if (!kPlayer->IsAnimating())
	{
		if (kPlayer->Lives() > 0)
		{
			if (kPlayerRespawnTimer == 0.0f)
				kPlayer->Visible(false);

			kPlayerRespawnTimer += kTimer->DeltaTime(); 

			if (kPlayerRespawnTimer >= kPlayerRespawnDelay)
			{
				kPlayer->Active(true); 
				kPlayer->Visible(true); 
				kPlayerHit = false; 
				kStars->Scroll(true); 
			}
		}
		else // player lives <= 0
		{
			if (kGameOverTimer == 0.0f)
				kPlayer->Visible(false);

			kGameOverTimer += kTimer->DeltaTime(); 

			if (kGameOverTimer >= kGameOverDelay)
				kCurrentState = gameover;
		}

	}
}

Level::LEVEL_STATE Level::State()
{
	return kCurrentState;
}

void Level::Update()
{
	if (!kStageStarted)
	{
		HandleStartLabels(); 
	}
	else 
	{	
		kEnemy->Update();
		HandleCollisions();

		if (kPlayerHit)
			HandlePlayerDeath(); 
		else 
		{
			if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_N))
				kCurrentState = finished; 
		}
	}
}

void Level::Render()
{
	if (!kStageStarted)
	{
		if (kLabelTimer > kStageLabelOnScreen && kLabelTimer < kStageLabelOffScreen)
		{
			kStageLabel->Render();
			kStageNumber->Render(); 
		}
		else if (kLabelTimer > kReadyLabelOnScreen && kLabelTimer < kReadyLabelOffScreen)
		{
			kReadyLabel->Render();
		}
	}
	else // stage started
	{	
		kEnemy->Render(); 

		if (kPlayerHit)
		{
			if (kPlayerRespawnTimer >= kPlayerRespawnLabelOnScreen)
				kReadyLabel->Render(); 

			if (kGameOverTimer >= kGameOverLabelOnScreen)
				kGameOverLabel->Render(); 
		}
	}
}