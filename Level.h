#ifndef _LEVEL_H
#define _LEVEL_H

#include "InputManager.h"
#include "PlayHUD.h"
#include "BackgroundStars.h"
#include "Player.h"
#include "Enemy.h"

class Level : public GameEntity
{
public:
	enum LEVEL_STATE { running, finished, gameover };

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

	bool kPlayerHit;
	float kPlayerRespawnDelay;
	float kPlayerRespawnTimer; 
	float kPlayerRespawnLabelOnScreen;  

	Texture* kGameOverLabel; 
	bool kGameOver; 
	float kGameOverDelay; 
	float kGameOverTimer; 
	float kGameOverLabelOnScreen; 

	LEVEL_STATE kCurrentState;

	Enemy* kEnemy; 

private: 
	void StartStage(); 
	void HandleStartLabels();
	void HandleCollisions(); 
	void HandlePlayerDeath();

public:
	Level(int stage, PlayHUD* hud, Player* player); 
	~Level(); 

	LEVEL_STATE State(); 

	void Update(); 
	void Render(); 
}; 

#endif