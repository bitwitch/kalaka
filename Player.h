#ifndef _PLAYER_H
#define _PLAYER_H

#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Bullet.h"

// using namespace Ather;

class Player : public GameEntity
{
private:
	Timer* kTimer; 
	InputManager* kInput; 
	AudioManager* kAudio;

	bool kVisible; 
	bool kAnimating; 

	int kScore; 
	int kLives; 

	Texture * kShip;

	AnimatedTexture* kDeathAnimation;

	float kMoveSpeed; 
	Vector2 kMoveBounds; 

	static const int MAX_BULLETS = 2; 
	Bullet* kBullets[MAX_BULLETS]; 

private:
	void HandleMovement(); 
	void HandleFiring();

public:
	Player(); 
	~Player();

	void Visible(bool visible);
	void AddScore(int change); 
	
	bool IsAnimating(); 
	int Score(); 
	int Lives(); 

	void WasHit();

	void Update(); 
	void Render();

};

#endif