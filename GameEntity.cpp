#include "GameEntity.h"

GameEntity::GameEntity(float x, float y) 
{
	kPos.x    = x; 
	kPos.y    = y; 
	kRotation = 0.0f; 
	kActive   = true; 
	kParent   = NULL; 
	kScale    = VEC2_ONE;
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

	Vector2 parentScale = kParent->Scale(world); 
	Vector2 rotPos = RotateVector(Vector2(kPos.x * parentScale.x, kPos.y * parentScale.y), kParent->Rotation(local)); 

	return kParent->Pos(world) + rotPos; 
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

void GameEntity::Scale(Vector2 scale)
{
	kScale = scale; 
}

void GameEntity::Scale(float scale)
{
	kScale = Vector2(scale, scale); 
}

Vector2 GameEntity::Scale(SPACE space)
{	
	if (space == local || kParent == NULL)
		return kScale;

	Vector2 scale = kParent->Scale(world); 
	scale.x *= kScale.x; 
	scale.y *= kScale.y; 
	return scale;  
}

void GameEntity::Translate(Vector2 vec)
{
	kPos += vec; 
}

void GameEntity::Rotate(float angle)
{
	kRotation += angle; 
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
	if (parent == NULL)
	{
		kPos = Pos(world); 
		kRotation = Rotation(world); 
		kScale = Scale(world); 
	}
	else 
	{
		if (kParent != NULL)
			Parent(NULL); 

		Vector2 parentScale = parent->Scale(world); 
		kPos = RotateVector(Pos(world) - parent->Pos(world), -parent->Rotation(world)); 
		kPos.x /= parentScale.x; 
		kPos.y /= parentScale.y; 

		kRotation -= parent->Rotation(world); 

		kScale = Vector2(kScale.x / parentScale.x, kScale.y / parentScale.y); 
	}
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
