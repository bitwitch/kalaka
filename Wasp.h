#ifndef _WASP_H
#define _WASP_H

#include "Enemy.h"

class Wasp : public Enemy
{
private: 
	bool kDiver;

private:
	Vector2 FormationPosition(); 
	Vector2 FlyInTargetPosition(); 

	void PathComplete();
	void FlyInComplete(); 

	void HandleDiveState(); 
	void HandleDeadState();

public:
	Wasp(int index, int path, bool challengeStage, bool diver);
	~Wasp();
};

#endif