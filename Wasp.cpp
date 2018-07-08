#include "Wasp.h"

std::vector<std::vector<Vector2> > Wasp::sDivePaths;

void Wasp::CreateDivePaths()
{
	// rhs wasps
	int currentPath = 0; 

	BezierCurve r0 = { Vector2(0.0f, 0.0f), Vector2(0.0f, -45.0f), Vector2(-60.0f, -45.0f), Vector2(-60.0f, 0.0f) };
	BezierCurve r1 = { Vector2(-60.0f, 0.0f), Vector2(-60.0f, 80.0f), Vector2(0.0f, 150.0f), Vector2(100.0f, 150.0f) };
	BezierCurve r2 = { Vector2(100.0f, 150.0f), Vector2(250.0f, 150.0f), Vector2(350.0f, 200.0f), Vector2(350.0f, 350.0f) };
	BezierCurve r3 = { Vector2(350.0f, 350.0f), Vector2(350.0f, 575.0f), Vector2(100.0f, 575.0f), Vector2(100.0f, 350.0f) };

	BezierPath* path = new BezierPath(); 
	path->AddCurve(r0, 15);
	path->AddCurve(r1, 15);
	path->AddCurve(r2, 15);
	path->AddCurve(r3, 15);

	sDivePaths.push_back(std::vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]);
	delete path; 

	// lhs wasps
	currentPath = 1; 

	BezierCurve l0 = { Vector2(0.0f, 0.0f), Vector2(0.0f, -45.0f), Vector2(60.0f, -45.0f), Vector2(60.0f, 0.0f) };
	BezierCurve l1 = { Vector2(60.0f, 0.0f), Vector2(60.0f, 80.0f), Vector2(0.0f, 150.0f), Vector2(-100.0f, 150.0f) };
	BezierCurve l2 = { Vector2(-100.0f, 150.0f), Vector2(-250.0f, 150.0f), Vector2(-350.0f, 200.0f), Vector2(-350.0f, 350.0f) };
	BezierCurve l3 = { Vector2(-350.0f, 350.0f), Vector2(-350.0f, 575.0f), Vector2(-100.0f, 575.0f), Vector2(-100.0f, 350.0f) };

	path = new BezierPath(); 
	path->AddCurve(l0, 15);
	path->AddCurve(l1, 15);
	path->AddCurve(l2, 15);
	path->AddCurve(l3, 15);

	sDivePaths.push_back(std::vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]);
	delete path; 
}

Wasp::Wasp(int index, int path, bool challengeStage, bool diver) 
	: Enemy(index, path, challengeStage)
{
	kDiver = diver;

	kTextures[0] = new Texture("galaga_spritesheet.png", 163, 179, 13, 10); 
	kTextures[0]->Parent(this); 
	kTextures[0]->Scale(4.0f); 
	kTextures[0]->Pos(VEC2_ZERO); 

	kTextures[1] = new Texture("galaga_spritesheet.png", 187, 179, 13, 10); 
	kTextures[1]->Parent(this); 
	kTextures[1]->Scale(4.0f); 
	kTextures[1]->Pos(VEC2_ZERO); 

	kType = wasp;
}

Wasp::~Wasp()
{

}

Vector2 Wasp::FormationPositionLocal()
{
	Vector2 retVal; 
	// calculate x pos in the formation
	retVal.x = (sFormation->GridSize().x + sFormation->GridSize().x * 2 * (kIndex / 4) ) * pow(-1, kIndex % 2 + 1);

	//calculate y pos in the formation
	retVal.y = (sFormation->GridSize().y * 2) + sFormation->GridSize().y * ((kIndex % 4) / 2);

	return retVal;  
}

void Wasp::PathComplete()
{
	Enemy::PathComplete(); 
}

void Wasp::FlyInComplete()
{
	if (kDiver)
		kCurrentState = dead; 
	else 
		Enemy::JoinFormation();
}

void Wasp::HandleDiveState() 
{
	int currentPath = kIndex % 2;

	if (kCurrentWaypoint < sDivePaths[currentPath].size())
	{
		Vector2 waypointPos = kDiveStartPos + sDivePaths[currentPath][kCurrentWaypoint];
		Vector2 dist = waypointPos - Pos(); 
		Translate(dist.Normalized() * kTimer->DeltaTime() * kSpeed, world);
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f); 

		if ( (waypointPos - Pos()).MagnitudeSqr() < EPSILON )
			kCurrentWaypoint++;
	}
	else
	{
		Vector2 dist = FormationPositionWorld() - Pos(); 
		Translate(dist.Normalized() * kTimer->DeltaTime() * kSpeed, world);
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f); 

		if (dist.MagnitudeSqr() < EPSILON)
			JoinFormation(); 
	}

}

void Wasp::HandleDeadState() 
{
	
}

void Wasp::RenderDiveState()
{	
	kTextures[0]->Render(); 

	int currentPath = kIndex % 2;

	for (int i=0; i < sDivePaths[currentPath].size() - 1; i++)
	{
		Graphics::Instance()->DrawLine(
			kDiveStartPos.x + sDivePaths[currentPath][i].x, 
			kDiveStartPos.y + sDivePaths[currentPath][i].y, 
			kDiveStartPos.x + sDivePaths[currentPath][i+1].x, 
			kDiveStartPos.y + sDivePaths[currentPath][i+1].y
			);
	}

	Vector2 finalPos   = FormationPositionWorld(); 
	Vector2 pathEndPos = kDiveStartPos + sDivePaths[currentPath][sDivePaths[currentPath].size() - 1];
	Graphics::Instance()->DrawLine(pathEndPos.x, pathEndPos.y, finalPos.x, finalPos.y);
}

void Wasp::RenderDeadState()
{
	
}