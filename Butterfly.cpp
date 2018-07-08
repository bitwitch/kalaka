#include "Butterfly.h"

Butterfly::Butterfly(int index, int path, bool challengeStage) 
	: Enemy(index, path, challengeStage)
{
	kTextures[0] = new Texture("galaga_spritesheet.png", 163, 155, 13, 10); 
	kTextures[0]->Parent(this); 
	kTextures[0]->Scale(4.0f); 
	kTextures[0]->Pos(VEC2_ZERO); 

	kTextures[1] = new Texture("galaga_spritesheet.png", 187, 155, 13, 10); 
	kTextures[1]->Parent(this); 
	kTextures[1]->Scale(4.0f); 
	kTextures[1]->Pos(VEC2_ZERO); 

	kType = butterfly;
}

Butterfly::~Butterfly()
{

}

Vector2 Butterfly::FormationPositionLocal()
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

void Butterfly::RenderDiveState() 
{
	
}

void Butterfly::RenderDeadState() 
{
	
}