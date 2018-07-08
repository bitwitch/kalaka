#ifndef _GAMEENTITY_H
#define _GAMEENTITY_H

#include "MathHelper.h"

class GameEntity 
{
public:

	enum SPACE {local, world}; 

private:

	Vector2 kPos;
	Vector2 kScale;
	float kRotation; 
	bool kActive; 
	GameEntity* kParent; 

public: 

	GameEntity(float x=0.0f, float y=0.0f);
	~GameEntity(); 

	void Pos(Vector2 pos); 
	Vector2 Pos(SPACE space=world); 

	void Rotation(float rotation); 
	float Rotation(SPACE space=world); 

	void Translate(Vector2 vec, SPACE space=local); 
	void Rotate(float angle); 

	void Active(bool active); 
	bool Active(); 

	void Scale(Vector2 scale); 
	void Scale(float scale); 
	Vector2 Scale(SPACE space=world);

	void Parent(GameEntity* parent); 
	GameEntity* Parent(); 

	virtual void Update(); 
	virtual void Render(); 
};

#endif
