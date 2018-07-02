#include "StartScreen.h"

StartScreen::StartScreen()
{	
	kTimer = Timer::Instance(); 
	kInput = InputManager::Instance(); 

	// Colors  TODO(shaw): move colors to a common location 
	SDL_Color ssRed = { 201, 31, 8 }; 
	SDL_Color ssWhite = { 230, 230, 230 }; 
	SDL_Color ssGreen = { 0, 194, 75 }; 

	// Top Bar
	kTopBar = new GameEntity(Graphics::Instance()->SCREEN_WIDTH*0.5f, 80.0f); 
	kPlayerOne = new Texture("1UP", "emulogic.ttf", 24, ssRed); 
	kHiScore   = new Texture("HI-Score", "emulogic.ttf", 24, ssRed); 
	kPlayerTwo = new Texture("2UP", "emulogic.ttf", 24, ssRed); 

	kPlayerOne->Parent(kTopBar);
	kHiScore->Parent(kTopBar);
	kPlayerTwo->Parent(kTopBar);

	kPlayerOne->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH*0.35f, 0.0f));
	kPlayerTwo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.2f, 0.0f));
	kHiScore->Pos(Vector2(-40.0f, 0.0f));

	kTopBar->Parent(this); 

	// Logo 
	kLogo = new Texture("kalaka_logo.png", 0, 0, 585, 140); 
	kLogo->Parent(this); 
	kLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.30f));

	kAnimatedLogo = new AnimatedTexture("kalaka_logo.png", 0, 0, 585, 140, 3, 0.5f, AnimatedTexture::vertical);
	kAnimatedLogo->Parent(this);
	kAnimatedLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.30f));

	// Play Mode
	kPlayModes = new GameEntity(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.55f);
	kOnePlayerMode = new Texture("1 Player", "emulogic.ttf", 24, ssWhite);
	kTwoPlayerMode = new Texture("2 Players", "emulogic.ttf", 24, ssWhite); 
	kCursor = new Texture("cursor.png"); 

	kOnePlayerMode->Parent(kPlayModes);
	kTwoPlayerMode->Parent(kPlayModes);
	kCursor->Parent(kPlayModes); 

	kOnePlayerMode->Pos(Vector2(-15.0f, -35.0f));
	kTwoPlayerMode->Pos(Vector2(0.0f, 35.0f));
	kCursor->Pos(Vector2(-150.0f, -35.0f));

	kPlayModes->Parent(this); 

	kCursorStartPos = kCursor->Pos(local); 
	kCursorOffset = Vector2(0.0f, 70.0f); 
	kSelectedMode = 0; 

	// Bottom Bar
	kBottomBar = new GameEntity(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.72f);
	kDoom = new Texture("doombox", "namco__.ttf", 32, ssRed); 
	kDates = new Texture("© 2018 Doombox Games LTD.", "emulogic.ttf", 24, ssWhite); 
	kRights = new Texture("All Rights Reserved", "emulogic.ttf", 24, ssWhite); 

	kDoom->Parent(kBottomBar); 
	kDates->Parent(kBottomBar); 
	kRights->Parent(kBottomBar); 

	kDoom->Pos(VEC2_ZERO);
	kDates->Pos(Vector2(0.0f, 100.0f));
	kRights->Pos(Vector2(0.0f, 150.0f));

	kBottomBar->Parent(this); 

	// Scroll Vars
	kScrollStart = Vector2(0.0f, Graphics::Instance()->SCREEN_HEIGHT);
	kScrollEnd = VEC2_ZERO;
	kScrollTotalTime = 5.0f;
	kScrollTimer = 0.0f;
	kScrollDone = false; 

	Pos(kScrollStart); 
}

StartScreen::~StartScreen()
{
	// Free Top Bar
	delete kTopBar; 
	kTopBar = NULL; 
	delete kPlayerOne; 
	kPlayerOne = NULL; 
	delete kPlayerTwo; 
	kPlayerTwo = NULL; 
	delete kHiScore; 
	kHiScore = NULL; 

	// Free Logo
	delete kLogo; 
	kLogo = NULL; 
	delete kAnimatedLogo; 
	kAnimatedLogo = NULL; 

	// Free Player Modes
	delete kOnePlayerMode; 
	kOnePlayerMode = NULL; 
	delete kTwoPlayerMode; 
	kTwoPlayerMode = NULL; 
	delete kCursor; 
	kCursor = NULL; 
	delete kPlayModes; 
	kPlayModes = NULL; 

	// Free Bottom Bar
	delete kDoom; 
	kDoom = NULL; 
	delete kDates; 
	kDates = NULL; 
	delete kRights; 
	kRights = NULL; 
	delete kBottomBar; 
	kBottomBar = NULL; 
}

void StartScreen::ChangeSelectedMode(int change)
{
	kSelectedMode += change; 
	if (kSelectedMode < 0)
		kSelectedMode = 1;
	else if (kSelectedMode > 1)
		kSelectedMode = 0; 

	kCursor->Pos(kCursorStartPos + kCursorOffset * kSelectedMode); 
}

void StartScreen::Update()
{	
	if (!kScrollDone)
	{	
		kScrollTimer = kScrollTimer + kTimer->DeltaTime();
		Pos(Lerp(kScrollStart, kScrollEnd, kScrollTimer / kScrollTotalTime)); 

		if (kScrollTimer >= kScrollTotalTime)
			kScrollDone = true; 
		
		if (kInput->KeyPressed(SDL_SCANCODE_UP) || kInput->KeyPressed(SDL_SCANCODE_DOWN))
		{
			kScrollTimer = kScrollTotalTime; 
		}
	}
	else 
	{
		kAnimatedLogo->Update();
		if (kInput->KeyPressed(SDL_SCANCODE_UP))
		{
			ChangeSelectedMode(-1); 
		}
		else if (kInput->KeyPressed(SDL_SCANCODE_DOWN))
		{
			ChangeSelectedMode(1); 
		}
	}
}

void StartScreen::Render()
{	
	// Top Bar
	kPlayerOne->Render();
	kPlayerTwo->Render();
	kHiScore->Render();

	// Logo
	if (kScrollDone)
		kAnimatedLogo->Render(); 
	else 
		kLogo->Render(); 

	// Player Modes
	kOnePlayerMode->Render(); 
	kTwoPlayerMode->Render(); 
	kCursor->Render(); 

	// Bottom Bar
	kDoom->Render();
	kDates->Render(); 
	kRights->Render();
}
