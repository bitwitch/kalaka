#include "Butterfly.h"

Butterfly::Butterfly(int index, int path, bool challengeStage) 
	: Enemy(index, path, challengeStage)
{
	if (!challengeStage)
		kTargetPos = FormationPosition(); 

	kTexture = new Texture("galaga_spritesheet.png", 163, 155, 13, 10); 
	kTexture->Parent(this); 
	kTexture->Scale(4.0f); 
	kTexture->Pos(VEC2_ZERO); 
}

Butterfly::~Butterfly()
{

}

Vector2 Butterfly::FormationPosition()
{
	Vector2 retVal; 
	// calculate x pos in the formation
	retVal.x = (sFormation->GridSize().x + sFormation->GridSize().x * 2 * (kIndex / 4) ) * pow(-1, kIndex % 2 + 1);

	//calculate y pos in the formation
	retVal.y = sFormation->GridSize().y * ((kIndex % 4) / 2);

	return retVal;  
}

void Butterfly::HandleDiveState() 
{

}


void Butterfly::HandleDeadState() 
{
	
}