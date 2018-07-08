#include "Enemy.h"

std::vector<std::vector<Vector2> > Enemy::sPaths; 

void Enemy::CreatePaths()
{	
	int screenMidPoint = Graphics::Instance()->SCREEN_WIDTH*0.38f;

	int currentPath = 0; 

	BezierCurve c0 = { Vector2(screenMidPoint + 50.0f, -10.0f), Vector2(screenMidPoint + 50.0f, -20.0f), Vector2(screenMidPoint + 50.0f, 30.0f), Vector2(screenMidPoint + 50.0f, 20.0f) };
	BezierCurve c1 = { Vector2(screenMidPoint + 50.0f, 20.0f), Vector2(screenMidPoint + 50.0f, 100.0f), Vector2(75.0f, 325.0f), Vector2(75.0f, 425.0f) };
	BezierCurve c2 = { Vector2(75.0f, 425.0f), Vector2(75.0f, 650.0f), Vector2(325.0f, 650.0f), Vector2(325.0f, 425.0f) };

	BezierPath* path = new BezierPath(); 
	path->AddCurve(c0, 1);
	path->AddCurve(c1, 25);
	path->AddCurve(c2, 25);

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

	kSpeed = 300.0f; 
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
		Translate(dist.Normalized() * kTimer->DeltaTime() * kSpeed, world); 
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);
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
