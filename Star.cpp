#include "Star.h"

bool Star::sScroll = false; 

void Star::Scroll(bool b)
{
	sScroll = b; 
}

Star::Star(int layer) : Texture("stars.png", 0, 0, 4, 4)
{
	kTimer = Timer::Instance(); 
	int starColor = rand() % 4;
	kClipRect.x = starColor * 4; 
	kFlickerTimer = 0.0f; 
	kFlickerSpeed = 0.15f + ((float)rand() / RAND_MAX) * 0.45f;    // 0.15 min    0.15 + 0.45 max
	kScrollSpeed = 10.0f / layer; 
	float invLayer = 1.0f / layer; 
	
	Pos(Vector2(rand() % Graphics::Instance()->SCREEN_WIDTH, rand() % Graphics::Instance()->SCREEN_HEIGHT));
	Scale(VEC2_ONE * invLayer); 
}

Star::~Star()
{
	kTimer = NULL; 
}

void Star::ScrollStar()
{
	Translate(VEC2_UP * kScrollSpeed); 
	Vector2 pos = Pos(local); 

	if (pos.y > Graphics::Instance()->SCREEN_HEIGHT)
	{
		pos.y = 0.0f; 
		pos.x = rand() % Graphics::Instance()->SCREEN_WIDTH; 
		Pos(pos); 
	}
}

void Star::Update()
{
	kFlickerTimer += kTimer->DeltaTime(); 
	if (kFlickerTimer >= kFlickerSpeed)
	{
		kVisible = !kVisible;
		kFlickerTimer = 0.0f; 
	}

	if (sScroll)
		ScrollStar(); 
}

void Star::Render()
{
	if (kVisible)
		Texture::Render(); 
}
