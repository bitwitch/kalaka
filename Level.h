#ifndef _LEVEL_H
#define _LEVEL_H

#include "InputManager.h"
#include "PlayHUD.h"
#include "BackgroundStars.h"
#include "Player.h"

class Level : public GameEntity
{
private:
	Timer* kTimer; 
	PlayHUD* kHUD; 
	BackgroundStars* kStars; 

	int kStage; 
	bool kStageStarted; 
	float kLabelTimer; 

	Texture* kStageLabel; 
	Scoreboard* kStageNumber;
	float kStageLabelOnScreen;
	float kStageLabelOffScreen; 

	Texture* kReadyLabel; 
	float kReadyLabelOnScreen;
	float kReadyLabelOffScreen;

	Player* kPlayer; 

private: 
	void StartStage(); 

public:
	Level(int stage, PlayHUD* hud, Player* player); 
	~Level(); 

	void Update(); 
	void Render(); 
}; 

#endif