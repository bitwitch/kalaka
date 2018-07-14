#ifndef  _BOSS_H
#define _BOSS_H

#include "Enemy.h"
#include "CaptureBeam.h"

class Boss : public Enemy
{
private: 
	static std::vector<std::vector<Vector2> > sDivePaths;
	int kCurrentPath; 
	bool kCaptureDive; 
	bool kCapturing; 
	CaptureBeam* kCaptureBeam; 

private:
	Vector2 FormationPositionLocal(); 

	void HandleDiveState(); 
	void HandleDeadState();
	void HandleCaptureBeam(); 

	void RenderDiveState(); 
	void RenderDeadState();

public:
	static void CreateDivePaths(); 

	void Dive(int type=0); 

	Boss(int index, int path, bool challengeStage);
	~Boss();
};

#endif