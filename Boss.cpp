#include "Boss.h"

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
}

Boss::~Boss()
{

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

}

void Boss::HandleDeadState() 
{
	
}

void Boss::RenderDiveState() 
{

}

void Boss::RenderDeadState() 
{

}