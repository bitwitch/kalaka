#include "Bullet.h"

Bullet::Bullet()
{
	kTimer = Timer::Instance();
	kSpeed = 1000.0f; 
	kTexture = new Texture("galaga_spritesheet.png", 367, 196, 3, 8);
	kTexture->Parent(this); 
	kTexture->Scale(4.0f);
	kTexture->Pos(VEC2_ZERO); 

	Reload(); 
}

void Bullet::Fire(Vector2 pos)
{
	Pos(pos); 
	Active(true); 
}

void Bullet::Reload()
{
	Active(false); 
}

Bullet::~Bullet()
{
	kTimer = NULL; 
	delete kTexture;
	kTexture = NULL; 
}

void Bullet::Update()
{
	if (Active())
	{
		Translate(-VEC2_UP * kSpeed * kTimer->DeltaTime(), local);
		Vector2 pos = Pos(); 

		if (pos.y < -OFFSCREEN_BUFFER || pos.y > Graphics::Instance()->SCREEN_HEIGHT + OFFSCREEN_BUFFER)
			Reload();
	}

}	

void Bullet::Render()
{
	if (Active())
		kTexture->Render();
}