#include "CaptureBeam.h"

CaptureBeam::CaptureBeam()
	: AnimatedTexture("galaga_spritesheet.png", 206, 104, 56, 80, 3, 0.5f, horizontal)
{
	kTotalCaptureTime = 6.0f; 
	ResetAnimation(); 
}

CaptureBeam::~CaptureBeam()
{

}

void CaptureBeam::ResetAnimation()
{
	AnimatedTexture::ResetAnimation(); 
	kCaptureTimer = 0.0f; 
	kClipRect.h = 0; 
}

void CaptureBeam::RunAnimation()
{
	kCaptureTimer += kTimer->DeltaTime(); 

	if (kCaptureTimer >= kTotalCaptureTime)
		kAnimationDone = true; 
	else 
	{
		kAnimationTimer += kTimer->DeltaTime(); 

		if (kAnimationTimer >= kAnimationSpeed)
			kAnimationTimer -= kAnimationSpeed;

		kClipRect.x = (int)(kAnimationTimer / kTimePerFrame) * kWidth; 

		if (kCaptureTimer < 2.0f) 
		{
			float temp = (int)(kCaptureTimer * 3.5f);
			kClipRect.h = (int)(temp / 7.0f) * kHeight; 
		}
		else if (kCaptureTimer > kTotalCaptureTime - 2.0f)
		{
			float temp = (kTotalCaptureTime - kCaptureTimer) * 3.5f; 
			kClipRect.h = (int)(temp / 7.0f) * kHeight; 
		}
		else 
		{
			kClipRect.h = kHeight; 
		}
	}
}

void CaptureBeam::Render()
{
	Vector2 pos = Pos(world); 
	Vector2 scale = Scale(world); 

	kRenderRect.x = (int)(pos.x - kWidth * scale.x * 0.5f);
	kRenderRect.y = (int)(pos.y - kHeight * scale.x * 0.5f);
	kRenderRect.w = (int)(kWidth * scale.x);
	kRenderRect.h = kClipRect.h; 

	kGraphics->DrawTexture(kTex, kClipped ? &kClipRect : NULL, &kRenderRect, Rotation(world)); 
}
