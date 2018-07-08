#include "Player.h"

Player::Player()
{
	kTimer = Timer::Instance(); 
	kInput = InputManager::Instance(); 
	kAudio = AudioManager::Instance(); 

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

	kDeathAnimation = new AnimatedTexture("galaga_spritesheet.png", 206, 48, 39, 32, 4, 1.0f, AnimatedTexture::horizontal);
	kDeathAnimation->Parent(this); 
	kDeathAnimation->Scale(4.0f); 
	kDeathAnimation->Pos(VEC2_ONE);
	kDeathAnimation->WrapMode(AnimatedTexture::once);
}

Player::~Player()
{
	kTimer = NULL; 
	kInput = NULL; 
	kAudio = NULL; 

	delete kShip;
	kShip = NULL; 
	delete kDeathAnimation;
	kDeathAnimation = NULL; 
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

void Player::WasHit()
{
	kLives--;
	kDeathAnimation->ResetAnimation();
	kAnimating = true; 
	kAudio->PlaySFX("splode.wav"); 
}

void Player::Update()
{
	if (kAnimating)
	{
		kDeathAnimation->Update(); 
		kAnimating = kDeathAnimation->IsAnimating();
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
			kDeathAnimation->Render();
		else 
			kShip->Render(); 
	}
}