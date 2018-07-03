#ifndef _PLAYHUD_H
#define _PLAYHUD_H

#include "Timer.h"
#include "Scoreboard.h"
#include "AudioManager.h"

class PlayHUD : public GameEntity 
{
private:
	Timer* kTimer; 
	AudioManager* kAudio; 

	Texture* kBackground;

	Texture* kHighLabel; 
	Texture* kScoreLabel;
	Scoreboard* kHighScoreboard;

	Texture* kPlayerOneLabel; 
	float kBlinkTimer;
	float kBlinkInterval;
	bool kPlayerOneLabelVisible; 
	Scoreboard* kPlayerOneScore;

public:
	PlayHUD();
	~PlayHUD();

	void Update(); 
	void Render(); 

	void SetHighScore(int score); 
	void SetPlayerScore(int score); 
};

#endif