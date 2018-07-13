#ifndef _ENEMY_H
#define _ENEMY_H

#include "AnimatedTexture.h"
#include "BezierPath.h"
#include "Formation.h"

class Enemy : public GameEntity
{
public:
	enum STATE { flyIn, formation, dive, dead };
	enum TYPE { butterfly, wasp, boss }; 

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

	TYPE kType;

	bool kChallengeStage; 

	Vector2 kDiveStartPos; 

protected:
	virtual void PathComplete();
	virtual void FlyInComplete();

	void JoinFormation(); 
	virtual Vector2 FormationPositionWorld();
	virtual Vector2 FormationPositionLocal() = 0;

	virtual void HandleFlyInState();
	virtual void HandleFormationState();
	virtual void HandleDiveState() = 0;
	virtual void HandleDeadState() = 0;

	void HandleStates(); 

	virtual void RenderFlyInState();
	virtual void RenderFormationState();
	virtual void RenderDiveState() = 0;
	virtual void RenderDeadState() = 0;
	
	void RenderStates();

public:
	static void SetFormation(Formation* f); 
	static void CreatePaths(); 

	Enemy(int index, int path, bool challengeStage); 
	virtual ~Enemy();

	STATE CurrentState();

	TYPE Type();
	int Index(); 

	virtual void Dive(int type=0);

	void Update(); 
	void Render(); 
};

#endif