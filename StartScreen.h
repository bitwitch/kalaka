#ifndef _STARTSCREEN_H
#define _STARTSCREEN_H

#include "AnimatedTexture.h"
#include "InputManager.h"
#include "BackgroundStars.h"

// using namespace Ather;

class StartScreen : public GameEntity
{
private:
	Timer* kTimer; 
	InputManager* kInput; 

	// Top Bar Entities
	GameEntity* kTopBar;
	Texture* kPlayerOne; 
	Texture* kHiScore; 
	Texture* kPlayerTwo; 

	// Logo
	Texture* kLogo;
	AnimatedTexture* kAnimatedLogo; 

	// Play Mode Entitites
	GameEntity* kPlayModes;
	Texture* kOnePlayerMode;
	Texture* kTwoPlayerMode;
	Texture* kCursor;
	Vector2 kCursorStartPos; 
	Vector2 kCursorOffset;
	int kSelectedMode; 


	// Bottom Bar Entities
	GameEntity* kBottomBar; 
	Texture* kDoom;
	Texture* kDates; 
	Texture* kRights; 

	// Scroll Vars
	Vector2 kScrollStart;
	Vector2 kScrollEnd; 
	float kScrollTotalTime;
	float kScrollTimer; 
	bool kScrollDone; 

	// Stars
	BackgroundStars* kStars; 
	
public:
	StartScreen();
	~StartScreen(); 

	void Update();
	void Render(); 
	void ChangeSelectedMode(int change); 
}; 

#endif