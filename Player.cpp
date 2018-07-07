#include "Player.h"

Player::Player()
{
	kTimer = Timer::Instance(); 
	kInput = InputManager::Instance(); 

	kVisible   = false; 
	kAnimating = false; 

	kScore = 0; 
	kLives = 2; 

	kShip = new Texture("galaga_spritesheet.png", 185, 56, 15, 16);
	kShip->Parent(this); 
	kShip->Scale(4.0f); 
	kShip->Pos(VEC2_ZERO); 

	kMoveSpeed = 275.0f; 
	kMoveBounds = Vector2(30.0f, 707.0f);
}

Player::~Player()
{
	kTimer = NULL; 
	kInput = NULL; 
	delete kShip;
	kShip = NULL; 
}

void Player::HandleMovement()
{
	if (kInput->KeyDown(SDL_SCANCODE_RIGHT))
	{
		Translate(VEC2_RIGHT * kMoveSpeed * kTimer->DeltaTime()); 
	}
	else if (kInput->KeyDown(SDL_SCANCODE_LEFT))
	{
		Translate(VEC2_LEFT * kMoveSpeed * kTimer->DeltaTime());
	}

	Vector2 pos = Pos(local); 

	if (pos.x < kMoveBounds.x)
		pos.x = kMoveBounds.x;
	else if (pos.x > kMoveBounds.y)
		pos.x = kMoveBounds.y; 

	Pos(pos); 
}

void Player::Visible(bool visible)
{
	kVisible = visible; 
}

bool Player::IsAnimating()
{
	return kAnimating; 
}

int Player::Score()
{
	return kScore; 
}

int Player::Lives()
{
	return kLives; 
}

void Player::AddScore(int change)
{
	kScore += change; 
}

void Player::Update()
{
	if (kAnimating)
	{

	}
	else
	{
		if (Active())
			HandleMovement(); 
	}
}

void Player::Render()
{
	if (kVisible)
	{
		if (kAnimating)
		{
			
		}
		else 
		{
			kShip->Render(); 
		}
	}
}