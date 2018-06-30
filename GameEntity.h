#ifndef _GAMEENTITY_H
#define _GAMEENTITY_H

#include "MathHelper.h"

class GameEntity 
{
public:

	enum SPACE {local, world}; 

private:

	Vector2 kPos;
	Vector2 kVel;
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

	void Translate(Vector2 vec); 

	void Active(bool active); 
	bool Active(); 

	void Parent(GameEntity* parent); 
	GameEntity* Parent(); 

	virtual void Update(); 
	virtual void Render(); 
};

#endif
