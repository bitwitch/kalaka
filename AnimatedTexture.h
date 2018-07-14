#ifndef _ANIMATEDTEXTURE_H
#define _ANIMATEDTEXTURE_H

#include "Timer.h"
#include "Texture.h"

class AnimatedTexture : public Texture 
{
public:
	enum WRAP_MODE { once, loop }; 
	enum ANIM_DIR { horizontal, vertical }; 

protected: 
	Timer* kTimer; 

	int kStartX; 
	int kStartY; 

	float kAnimationTimer; 
	float kAnimationSpeed; 
	float kTimePerFrame; 

	int kFrameCount;

	WRAP_MODE kWrapMode; 
	ANIM_DIR kAnimationDirection; 

	bool kAnimationDone; 

protected: 
	virtual void RunAnimation(); 

public: 
	AnimatedTexture(
		std::string filename, 
		int x, 
		int y, 
		int w, 
		int h, 
		int frameCount, 
		float animationSpeed, 
		ANIM_DIR animationDirection
		);
		
	~AnimatedTexture();

	void WrapMode(WRAP_MODE mode);

	virtual void ResetAnimation();

	bool IsAnimating();

	void Update(); 
}; 
#endif