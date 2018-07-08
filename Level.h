#ifndef _LEVEL_H
#define _LEVEL_H

#include "InputManager.h"
#include "PlayHUD.h"
#include "BackgroundStars.h"
#include "Player.h"
#include "Butterfly.h"
#include "Wasp.h"
#include "Boss.h"

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

	Formation* kFormation;

	int kButterflyCount;
	const int MAX_BUTTERFLIES = 16; 

	int kWaspCount;
	const int MAX_WASPS = 20; 

	int kBossCount;
	const int MAX_BOSSES = 4; 

	std::vector<Enemy*> kEnemies;

private: 
	void StartStage(); 
	void HandleStartLabels();
	void HandleCollisions(); 
	void HandlePlayerDeath();
	
	void HandleEnemySpawn(); 

	void HandleEnemyFormation();

public:
	Level(int stage, PlayHUD* hud, Player* player); 
	~Level(); 

	LEVEL_STATE State(); 

	void Update(); 
	void Render(); 
}; 

#endif