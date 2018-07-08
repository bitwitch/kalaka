#include "Wasp.h"

Wasp::Wasp(int index, int path, bool challengeStage, bool diver) 
	: Enemy(index, path, challengeStage)
{
	if (!challengeStage)
		kTargetPos = FormationPosition(); 

	kDiver = diver;

	kTexture = new Texture("galaga_spritesheet.png", 163, 179, 13, 10); 
	kTexture->Parent(this); 
	kTexture->Scale(4.0f); 
	kTexture->Pos(VEC2_ZERO); 
}

Wasp::~Wasp()
{

}

Vector2 Wasp::FlyInTargetPosition()
{
	return kDiver ? kTargetPos : Enemy::FlyInTargetPosition();
}


Vector2 Wasp::FormationPosition()
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
	if (kDiver)
		kTargetPos = VEC2_ZERO;
	else 
		Enemy::PathComplete(); 
}

void Wasp::FlyInComplete()
{
	if (kDiver)
		kCurrentState = dead; 
	else 
		Enemy::FlyInComplete();
}

void Wasp::HandleDiveState() 
{

}

void Wasp::HandleDeadState() 
{
	
}