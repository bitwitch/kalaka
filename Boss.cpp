#include "Boss.h"

Boss::Boss(int index, int path, bool challengeStage) 
	: Enemy(index, path, challengeStage)
{
	if (!challengeStage)
		kTargetPos = FormationPosition(); 

	kTexture = new Texture("galaga_spritesheet.png", 162, 104, 15, 16); 
	kTexture->Parent(this); 
	kTexture->Scale(4.0f); 
	kTexture->Pos(VEC2_ZERO); 
}

Boss::~Boss()
{

}

Vector2 Boss::FormationPosition()
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

}


void Boss::HandleDeadState() 
{
	
}