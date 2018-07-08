#ifndef _PLAYSCREEN_H
#define _PLAYSCREEN_H

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

	// Pass player so that player instance can be moved from one level to next
	Player* kPlayer; 

private:
	void StartNextLevel(); 

public: 
	PlayScreen();
	~PlayScreen();

	void StartNewGame(); 

	bool GameOver();

	void Update(); 
	void Render(); 
};

#endif