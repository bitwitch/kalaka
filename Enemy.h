#ifndef _ENEMY_H
#define _ENEMY_H

#include "AnimatedTexture.h"
#include " BezierPath.h"

class Enemy : public GameEntity
{
private:
	enum STATE { flyIn, formation, dive, dead };

	static std::vector<std::vector<Vector2> > sPaths;

	Timer* kTimer; 
	Texture* kTexture; 

	STATE kCurrentState; 

	int kCurrentPath; 

	int kCurrentWaypoint; 
	const float EPSILON = 8.0f;  

	float kSpeed; 

public:
	static void CreatePaths(); 

	Enemy(int path); 
	virtual ~Enemy();

	virtual void HandleFlyInState();
	virtual void HandleFormationState();
	virtual void HandleDiveState();
	virtual void HandleDeadState();

	void HandleStates(); 
	void Update(); 
	void Render(); 
};

#endif