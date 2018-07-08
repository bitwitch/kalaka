#ifndef  _BOSS_H
#define _BOSS_H

#include "Enemy.h"

class Boss : public Enemy
{
private:
	Vector2 FormationPosition(); 

	void HandleDiveState(); 
	void HandleDeadState();

public:
	Boss(int index, int path, bool challengeStage);
	~Boss();
};

#endif