#include "Boss.h"

std::vector<std::vector<Vector2> > Boss::sDivePaths;

void Boss::CreateDivePaths()
{
	int currentPath = 0; 

	BezierCurve l0 = { Vector2(0.0f, 0.0f), Vector2(0.0f, -60.0f), Vector2(-90.0f, -60.0f), Vector2(-90.0f, 0.0f) };
	BezierCurve l1 = { Vector2(-90.0f, 0.0f), Vector2(-90.0f, 60.0f), Vector2(-100.0f, 272.0f), Vector2(-15.0f, 275.0f) };
	BezierCurve l2 = { Vector2(-15.0f, 275.0f), Vector2(85.0f, 275.0f), Vector2(85.0f, 125.0f), Vector2(-15.0f, 125.0f) };
	BezierCurve l3 = { Vector2(-15.0f, 125.0f), Vector2(-175.0f, 125.0f), Vector2(0.0f, 450.0f), Vector2(120.0f, 450.0f) };
	BezierCurve l4 = { Vector2(120.0f, 450.0f), Vector2(160.0f, 450.0f), Vector2(200.0f, 500.0f), Vector2(200.0f, 550.0f) };
	BezierCurve l5 = { Vector2(200.0f, 550.0f), Vector2(200.0f, 540.0f), Vector2(200.0f, 800.0f), Vector2(200.0f, 790.0f) };

	BezierPath* path = new BezierPath(); 

	path->AddCurve(l0, 15); 
	path->AddCurve(l1, 15);
	path->AddCurve(l2, 15); 
	path->AddCurve(l3, 25);
	path->AddCurve(l4, 15);
	path->AddCurve(l5, 1);

	sDivePaths.push_back(std::vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]); 
	delete path; 


	currentPath = 1; 

	BezierCurve r0 = { Vector2(0.0f, 0.0f), Vector2(0.0f, -60.0f), Vector2(90.0f, -60.0f), Vector2(90.0f, 0.0f) };
	BezierCurve r1 = { Vector2(90.0f, 0.0f), Vector2(90.0f, 60.0f), Vector2(100.0f, 272.0f), Vector2(15.0f, 275.0f) };
	BezierCurve r2 = { Vector2(15.0f, 275.0f), Vector2(-85.0f, 275.0f), Vector2(-85.0f, 125.0f), Vector2(15.0f, 125.0f) };
	BezierCurve r3 = { Vector2(15.0f, 125.0f), Vector2(175.0f, 125.0f), Vector2(0.0f, 450.0f), Vector2(-120.0f, 450.0f) };
	BezierCurve r4 = { Vector2(-120.0f, 450.0f), Vector2(-160.0f, 450.0f), Vector2(-200.0f, 500.0f), Vector2(-200.0f, 550.0f) };
	BezierCurve r5 = { Vector2(-200.0f, 550.0f), Vector2(-200.0f, 540.0f), Vector2(-200.0f, 800.0f), Vector2(-200.0f, 790.0f) };

	path = new BezierPath(); 

	path->AddCurve(r0, 15); 
	path->AddCurve(r1, 15);
	path->AddCurve(r2, 15); 
	path->AddCurve(r3, 25);
	path->AddCurve(r4, 15);
	path->AddCurve(r5, 1);

	sDivePaths.push_back(std::vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]); 
	delete path;

	// Capture Dive Paths
	currentPath = 2; 

	BezierCurve cl0 = { Vector2(0.0f, 0.0f), Vector2(0.0f, -60.0f), Vector2(-90.0f, -60.0f), Vector2(-90.0f, 0.0f) };
	BezierCurve cl1 = { Vector2(-90.0f, 0.0f), Vector2(-90.0f, 60.0f), Vector2(100.0f, 340.0f), Vector2(100.0f, 400.0f) };

	path = new BezierPath(); 

	path->AddCurve(cl0, 15); 
	path->AddCurve(cl1, 15);

	sDivePaths.push_back(std::vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]); 
	delete path;

	currentPath = 3; 

	BezierCurve rl0 = { Vector2(0.0f, 0.0f), Vector2(0.0f, -60.0f), Vector2(90.0f, -60.0f), Vector2(90.0f, 0.0f) };
	BezierCurve rl1 = { Vector2(90.0f, 0.0f), Vector2(90.0f, 60.0f), Vector2(-100.0f, 340.0f), Vector2(-100.0f, 400.0f) };

	path = new BezierPath(); 

	path->AddCurve(rl0, 15); 
	path->AddCurve(rl1, 15);

	sDivePaths.push_back(std::vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]); 
	delete path;
}

Boss::Boss(int index, int path, bool challengeStage) 
	: Enemy(index, path, challengeStage)
{
	kTextures[0] = new Texture("galaga_spritesheet.png", 162, 104, 15, 16); 
	kTextures[0]->Parent(this); 
	kTextures[0]->Scale(4.0f); 
	kTextures[0]->Pos(VEC2_ZERO); 

	kTextures[1] = new Texture("galaga_spritesheet.png", 186, 104, 15, 16); 
	kTextures[1]->Parent(this);
	kTextures[1]->Scale(4.0f);
	kTextures[1]->Pos(VEC2_ZERO); 

	kType = boss; 
	kCurrentPath = 1; 
	kCaptureDive = false; 
	kCapturing = false;

	kCaptureBeam = new CaptureBeam(); 
	kCaptureBeam->Scale(4.0f); 
	kCaptureBeam->Parent(this); 
	kCaptureBeam->Pos(Vector2(0.0f, -190.0f));
	kCaptureBeam->Rotation(180.0f); 
}

Boss::~Boss()
{
	delete kCaptureBeam; 
	kCaptureBeam = NULL;
}

Vector2 Boss::FormationPositionLocal()
{
	Vector2 retVal; 
	// calculate x pos in the formation
	retVal.x = (sFormation->GridSize().x + sFormation->GridSize().x * 2 * (kIndex / 2) ) * pow(-1, kIndex % 2 + 1);

	//calculate y pos in the formation
	retVal.y = -sFormation->GridSize().y;

	return retVal;  
}

void Boss::HandleDiveState() 
{
	
	if (kCurrentWaypoint < sDivePaths[kCurrentPath].size())
	{
		Vector2 waypointPos = kDiveStartPos + sDivePaths[kCurrentPath][kCurrentWaypoint];
		Vector2 dist = waypointPos - Pos(); 
		Translate(dist.Normalized() * kTimer->DeltaTime() * kSpeed, world);
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f); 

		if ( (waypointPos - Pos()).MagnitudeSqr() < EPSILON )
			kCurrentWaypoint++;

		if (kCurrentWaypoint == sDivePaths[kCurrentPath].size())
		{
			if (kCaptureDive)
			{
				kCapturing = true; 
				Rotation(180.0f); 
			}
			else 
			{
				Pos(Vector2(FormationPositionWorld().x, -20.0f));
			}
		}
	}
	else
	{
		if (!kCaptureDive || !kCapturing)
		{
			Vector2 dist = FormationPositionWorld() - Pos(); 
			Translate(dist.Normalized() * kTimer->DeltaTime() * kSpeed, world);
			Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f); 

			if (dist.MagnitudeSqr() < EPSILON)
			{
				JoinFormation(); 
			}
		}
		else 
		{
			HandleCaptureBeam(); 
		}
	}
}

void Boss::HandleDeadState() 
{
	
}

void Boss::HandleCaptureBeam()
{
	kCaptureBeam->Update(); 

	if (!kCaptureBeam->IsAnimating())
	{
		Translate(VEC2_UP * kSpeed * kTimer->DeltaTime(), world); 
		if (Pos().y >= Graphics::Instance()->SCREEN_HEIGHT)
			Pos(Vector2(FormationPositionWorld().x, -20.0f)); 
	}
}

void Boss::RenderDiveState() 
{
	kTextures[0]->Render(); 

	for (int i=0; i < sDivePaths[kCurrentPath].size() - 1; i++)
	{
		Graphics::Instance()->DrawLine(
			kDiveStartPos.x + sDivePaths[kCurrentPath][i].x, 
			kDiveStartPos.y + sDivePaths[kCurrentPath][i].y, 
			kDiveStartPos.x + sDivePaths[kCurrentPath][i+1].x, 
			kDiveStartPos.y + sDivePaths[kCurrentPath][i+1].y
			);
	}

	if (kCapturing && kCaptureBeam->IsAnimating())
		kCaptureBeam->Render();
}

void Boss::RenderDeadState() 
{

}

void Boss::Dive(int type)
{
	kCaptureDive = (type != 0);
	Enemy::Dive();

	if (kCaptureDive)
	{
		kCapturing = false; 
		kCurrentPath = 2 + rand() % 2; 
	}
	else 
	{
		kCurrentPath = kIndex % 2;
	}
}
