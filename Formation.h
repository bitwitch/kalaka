#ifndef _FORMATION_H
#define _FORMATION_H

#include "GameEntity.h"
#include "Timer.h"

// using namespace "Ather";

class Formation : public GameEntity
{
private:
	Timer* kTimer; 

	float kOffsetAmount;
	float kOffsetTimer; 
	float kOffsetDelay;
	int kOffsetCounter; 
	int kOffsetDirection; 

	float kSpreadTimer; 
	float kSpreadDelay; 
	int kSpreadCounter; 
	int kSpreadDirection; 

	Vector2 kGridSize; 

	bool kLocked; 

public:
	Formation(); 
	~Formation(); 

	Vector2 GridSize(); 

	int GetTick(); 

	void Lock(); 
	bool Locked();
	
	void Update(); 
	
};

#endif