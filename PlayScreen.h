#ifndef _PLAYSCREEN_H
#define _PLAYSCREEN_H

#include "InputManager.h"
#include "BackgroundStars.h"
#include "PlayHUD.h"
#include "Level.h"

class PlayScreen : public GameEntity
{
private: 
	Timer* kTimer; 
	InputManager* kInput; 
	AudioManager* kAudio; 

	BackgroundStars* kStars;
	PlayHUD* kHUD;

	Texture* kStartLabel;
	float kLevelStartTimer; 
	float kLevelStartDelay;

	bool kGameStarted; 

	Level* kLevel; 
	
	bool kLevelStarted; 
	int kCurrentStage; 

private:
	void StartNextLevel(); 

public: 
	PlayScreen();
	~PlayScreen();

	void StartNewGame(); 

	void Update(); 
	void Render(); 
};

#endif