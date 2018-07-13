#ifndef _BUTTERFLY_H
#define _BUTTERFLY_H

#include "Enemy.h"

class Butterfly : public Enemy
{
private: 
	static std::vector<std::vector<Vector2> > sDivePaths;
	bool kEscort;

private:
	Vector2 FormationPositionLocal(); 

	void HandleDiveState(); 
	void HandleDeadState();

	void RenderDiveState();
	void RenderDeadState();

public:
	static void CreateDivePaths(); 
	
	void Dive(int type=0); 

	Butterfly(int index, int path, bool challengeStage);
	~Butterfly();

};

#endif