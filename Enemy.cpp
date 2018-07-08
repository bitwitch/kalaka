#include "Enemy.h"

std::vector<std::vector<Vector2> > Enemy::sPaths; 

void Enemy::CreatePaths()
{
	int currentPath = 0; 
	BezierPath* path = new BezierPath(); 
	BezierCurve curve = { Vector2(500.0f, 10.0f), Vector2(500.0f, 0.0f), Vector2(500.0f, 310.0f), Vector2(500.0f, 300.0f) };
	path->AddCurve(curve, 1);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path; 
}

Enemy::Enemy(int path)
{
	kTimer = Timer::Instance(); 
	kCurrentPath = path; 
	kCurrentState = flyIn; 
	kCurrentWaypoint = 0; 
	Pos(sPaths[kCurrentPath][kCurrentWaypoint]);

	kTexture = new Texture("galaga_spritesheet.png", 163, 153, 13, 14); 
	kTexture->Parent(this); 
	kTexture->Scale(4.0f); 
	kTexture->Pos(VEC2_ZERO); 

	kSpeed = 100.0f; 
}

Enemy::~Enemy()
{
	kTimer = NULL; 
	delete kTexture; 
	kTexture = NULL; 
}

void Enemy::HandleFlyInState()
{

	if ( (sPaths[kCurrentPath][kCurrentWaypoint] - Pos()).MagnitudeSqr() < EPSILON )
		kCurrentWaypoint++;

	if (kCurrentWaypoint < sPaths[kCurrentPath].size())
	{
		Vector2 dist = sPaths[kCurrentPath][kCurrentWaypoint] - Pos();
		Translate(dist.Normalized() * kTimer->DeltaTime() * kSpeed); 
	}
	else 
	{
		kCurrentState = formation; 
	}
}

void Enemy::HandleFormationState()
{
	
}

void Enemy::HandleDiveState()
{
	
}

void Enemy::HandleDeadState()
{
	
}

void Enemy::HandleStates()
{
	switch(kCurrentState)
	{
	case flyIn:
		HandleFlyInState();
		break;

	case formation:
		HandleFormationState();
		break;

	case dive:
		HandleDiveState();
		break;

	case dead:
		HandleDeadState();
		break;
	}
}

void Enemy::Update()
{
	if (Active())
		HandleStates(); 
}

void Enemy::Render()
{
	if (Active())
	{
		kTexture->Render(); 
		for (int i=0; i < sPaths[kCurrentPath].size() - 1; i++)
		{
			Graphics::Instance()->DrawLine(sPaths[kCurrentPath][i].x, sPaths[kCurrentPath][i].y, sPaths[kCurrentPath][i+1].x, sPaths[kCurrentPath][i+1].y);
		}
	}
}
