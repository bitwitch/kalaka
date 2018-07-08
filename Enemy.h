#ifndef _ENEMY_H
#define _ENEMY_H

#include "AnimatedTexture.h"
#include "BezierPath.h"
#include "Formation.h"

class Enemy : public GameEntity
{
public:
	enum STATE { flyIn, formation, dive, dead };

protected:

	static std::vector<std::vector<Vector2> > sPaths;
	static Formation* sFormation; 

	Timer* kTimer; 

	Texture* kTextures[2]; 

	STATE kCurrentState; 

	int kCurrentPath; 

	int kCurrentWaypoint; 
	const float EPSILON = 8.0f;  

	float kSpeed; 

	int kIndex; 

	Vector2 kTargetPos; 

	bool kChallengeStage; 

protected:
	virtual void HandleFlyInState();
	virtual void HandleFormationState();
	virtual void HandleDiveState() = 0;
	virtual void HandleDeadState() = 0;

	virtual void PathComplete();
	virtual Vector2 FlyInTargetPosition();
	virtual void FlyInComplete();

	virtual Vector2 FormationPosition() = 0;
	
	void HandleStates(); 

public:
	static void SetFormation(Formation* f); 
	static void CreatePaths(); 

	Enemy(int index, int path, bool challengeStage); 
	virtual ~Enemy();

	STATE CurrentState();

	void Update(); 
	void Render(); 
};

#endif