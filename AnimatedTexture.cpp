#include "AnimatedTexture.h"

 AnimatedTexture::AnimatedTexture(
		std::string filename, 
		int x, int y, 
		int w, int h, 
		int frameCount, 
		float animationSpeed, 
		ANIM_DIR animationDirection
 		) : Texture(filename, x, y, w, h)
{
	kTimer = Timer::Instance(); 
	kStartX = x; 
	kStartY = y;
	kFrameCount = frameCount; 
	kAnimationSpeed = animationSpeed; 
	kTimePerFrame = animationSpeed / kFrameCount; 
	kAnimationTimer = 0.0f; 
	kAnimationDirection = animationDirection;
	kAnimationDone = false; 
	kWrapMode = loop;
}

AnimatedTexture::~AnimatedTexture() {}

void AnimatedTexture::WrapMode(WRAP_MODE mode) 
{
	kWrapMode = mode; 
}

void AnimatedTexture::ResetAnimation()
{
	kAnimationTimer = 0.0f; 
	kAnimationDone = false;
}

bool AnimatedTexture::IsAnimating()
{
	return !kAnimationDone;
}

void AnimatedTexture::Update() 
{
	
	if (!kAnimationDone)
	{
		kAnimationTimer += kTimer->DeltaTime(); 

		if (kAnimationTimer >= kAnimationSpeed)
		{
			if (kWrapMode == loop) 
			{
				kAnimationTimer -= kAnimationSpeed;
				// kAnimationTimer = 0.0f;
			}
			else 
			{
				kAnimationDone = true; 
				kAnimationTimer = kAnimationSpeed - kTimePerFrame;
			}
		}

		if (kAnimationDirection == horizontal)
		{
			kClipRect.x = kStartX + (int)(kAnimationTimer / kTimePerFrame) * kWidth; 
		}
		else 
		{	
			kClipRect.y = kStartY + (int)(kAnimationTimer / kTimePerFrame) * kHeight; 
		}
	}
}

