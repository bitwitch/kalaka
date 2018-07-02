#ifndef _STAR_H
#define _STAR_H

#include "Timer.h"
#include "Texture.h"

// using namespace Aether;

class Star : public Texture 
{
private:
	static bool sScroll; 

	Timer* kTimer; 

	bool kVisible; 
	float kFlickerTimer; 
	float kFlickerSpeed; 
	float kScrollSpeed; 

public: 
	static void Scroll(bool b); 

	Star(int layer);
	~Star(); 

	void Update(); 
	void Render(); 

private:
	void ScrollStar(); 
};

#endif