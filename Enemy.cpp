#include "Enemy.h"

std::vector<std::vector<Vector2> > Enemy::sPaths; 
Formation* Enemy::sFormation = NULL; 

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

void Enemy::SetFormation(Formation* f)
{
	sFormation = f; 
}

Enemy::Enemy(int index, int path, bool challengeStage)
{	
	kIndex = index; 
	kChallengeStage = challengeStage;

	kTimer = Timer::Instance(); 
	kCurrentPath = path; 
	kCurrentState = flyIn; 
	kCurrentWaypoint = 1; 
	Pos(sPaths[kCurrentPath][0]);

	for (int i=0; i<2; i++)
		kTextures[i] = NULL; 

	kSpeed = 300.0f; 
}

Enemy::~Enemy()
{
	kTimer = NULL; 

	for (int i=0; i<2; i++)
	{
		delete kTextures[i]; 
		kTextures[i] = NULL; 
	}
}

void Enemy::PathComplete()
{
	if (kChallengeStage)
		kCurrentState = dead;
}

void Enemy::JoinFormation()
{
	Pos(FormationPositionWorld());
	Rotation(0); 
	Parent(sFormation);   
	kCurrentState = formation; 
}

Vector2 Enemy::FormationPositionWorld()
{
	return sFormation->Pos() + FormationPositionLocal();
}

void Enemy::FlyInComplete()
{
	if (kChallengeStage)
		kCurrentState = dead; 
	else 
		JoinFormation(); 
}

void Enemy::HandleFlyInState()
{
	if (kCurrentWaypoint < sPaths[kCurrentPath].size())
	{
		Vector2 dist = sPaths[kCurrentPath][kCurrentWaypoint] - Pos();
		Translate(dist.Normalized() * kTimer->DeltaTime() * kSpeed, world); 
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

		if ( (sPaths[kCurrentPath][kCurrentWaypoint] - Pos()).MagnitudeSqr() < EPSILON )
			kCurrentWaypoint++;

		if (kCurrentWaypoint >= sPaths[kCurrentPath].size())
			PathComplete(); 
	}
	else 
	{
		Vector2 dist = FormationPositionWorld() - Pos(); 
		Translate(dist.Normalized() * kTimer->DeltaTime() * kSpeed, world); 
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

		if (dist.MagnitudeSqr() < EPSILON)
			FlyInComplete();
	}
}

void Enemy::HandleFormationState()
{
	Pos(FormationPositionLocal()); 
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

void Enemy::RenderFlyInState()
{
	kTextures[0]->Render(); 
}

void Enemy::RenderFormationState()
{
	kTextures[sFormation->GetTick() % 2]->Render();
}

void Enemy::RenderStates()
{
	switch(kCurrentState)
	{
	case flyIn:
		RenderFlyInState();
		break;
	
	case formation:
		RenderFormationState();
		break;

	case dive:
		RenderDiveState();
		break;

	case dead:
		RenderDeadState();
		break;
	}
}

Enemy::STATE Enemy::CurrentState()
{
	return kCurrentState; 
}

Enemy::TYPE Enemy::Type()
{
	return kType;
}

int Enemy::Index() 
{
	return kIndex; 
}

void Enemy::Dive(int type)
{	
	// break away from formation
	Parent(NULL); 

	kCurrentState = dive; 
	kDiveStartPos = Pos(); 
	kCurrentWaypoint = 1; 
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
		RenderStates(); 

		// NOTE(shaw): render path for debugging
		// for (int i=0; i < sPaths[kCurrentPath].size() - 1; i++)
		// {
		// 	Graphics::Instance()->DrawLine(sPaths[kCurrentPath][i].x, sPaths[kCurrentPath][i].y, sPaths[kCurrentPath][i+1].x, sPaths[kCurrentPath][i+1].y);
		// }
	}
}
