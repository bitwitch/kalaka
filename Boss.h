#ifndef  _BOSS_H
#define _BOSS_H

#include "Enemy.h"

class Boss : public Enemy
{
private:
	Vector2 FormationPositionLocal(); 

	void HandleDiveState(); 
	void HandleDeadState();

	void RenderDiveState(); 
	void RenderDeadState();

public:
	Boss(int index, int path, bool challengeStage);
	~Boss();
};

#endif