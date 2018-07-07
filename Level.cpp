#include "Level.h"

Level::Level(int stage, PlayHUD* hud)
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
	kStageLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.34f, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

	kStageNumber = new Scoreboard(lightBlue);

	kStageNumber->Score(kStage); 
	kStageNumber->Parent(this); 
	kStageNumber->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

	kStageLabelOnScreen = 0.0f; 
	kStageLabelOffScreen = 1.5f;
	
	kReadyLabel = new Texture("READY", "emulogic.ttf", 24, desatRed); 
	kReadyLabel->Parent(this);
	kReadyLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.37f, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

	kReadyLabelOnScreen = kStageLabelOffScreen;
	kReadyLabelOffScreen = kReadyLabelOnScreen + 3.0f;
}

Level::~Level()
{
	kTimer = NULL; 
	kHUD = NULL; 
	kStars = NULL; 
	delete kStageLabel;
	kStageLabel = NULL; 
	delete kStageNumber;
	kStageNumber = NULL; 
	delete kReadyLabel;
	kReadyLabel = NULL; 
}

void Level::StartStage()
{	
	// TODO(shaw): spawn shit
	kStageStarted = true; 
}

void Level::Update()
{
	if (!kStageStarted)
	{
		kLabelTimer += kTimer->DeltaTime(); 
		if (kLabelTimer >= kStageLabelOffScreen)
		{
			kStars->Scroll(true);

			if (kStage > 1)
				StartStage();
			else if (kLabelTimer >= kReadyLabelOffScreen)
				StartStage();
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
	// else render all other shit
}