#include "GameEntity.h"

GameEntity::GameEntity(float x, float y) 
{
	kPos.x    = x; 
	kPos.y    = y; 
	kRotation = 0.0f; 
	kActive   = true; 
	kParent   = NULL; 
}

GameEntity::~GameEntity()
{
	kParent = NULL;
} 

void GameEntity::Pos(Vector2 pos)
{
	kPos = pos;
}

Vector2 GameEntity::Pos(SPACE space)
{
	if (space == local || kParent == NULL)
		return kPos;

	return kParent->Pos(world) + RotateVector(kPos, kParent->Rotation(local));
}

void GameEntity::Rotation(float r)
{
	kRotation = r; 

	if(kRotation > 360.0f) 
	{
		int mul = kRotation / 360;
		kRotation -= 360.0f * mul;
	}
	else if(kRotation < 0.0f) 
	{
		int mul = (kRotation / 360) - 1;
		kRotation -= 360.0f * mul;
	}
}

float GameEntity::Rotation(SPACE space)
{
	if (space == local || kParent == NULL)
		return kRotation;
	
	return kParent->Rotation(world) + kRotation; 
}

void GameEntity::Translate(Vector2 vec)
{
	kPos += vec; 
}

void GameEntity::Active(bool active)
{
	kActive = active; 
}

bool GameEntity::Active()
{
	return kActive;
}

void GameEntity::Parent(GameEntity* parent)
{
	kPos    = Pos(world) - parent->Pos(world); 
	kParent = parent; 
}

GameEntity* GameEntity::Parent()
{
	return kParent; 
}

void GameEntity::Update()
{

}

void GameEntity::Render()
{
	
}
