#ifndef _PLAYER_H
#define _PLAYER_H

#include "AnimatedTexture.h"
#include "InputManager.h"

// using namespace Ather;

class Player : public GameEntity
{
private:
	Timer* kTimer; 
	InputManager* kInput; 

	bool kVisible; 
	bool kAnimating; 

	int kScore; 
	int kLives; 

	Texture * kShip;

	float kMoveSpeed; 
	Vector2 kMoveBounds; 

private:
	void HandleMovement(); 

public:
	Player(); 
	~Player();

	void Visible(bool visible);
	bool IsAnimating(); 
	int Score(); 
	int Lives(); 
	void AddScore(int change); 

	void Update(); 
	void Render();

};

#endif