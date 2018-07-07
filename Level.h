#ifndef _LEVEL_H
#define _LEVEL_H

#include "InputManager.h"
#include "PlayHUD.h"
#include "BackgroundStars.h"

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

private: 
	void StartStage(); 

public:
	Level(int stage, PlayHUD* hud); 
	~Level(); 

	void Update(); 
	void Render(); 
}; 

#endif