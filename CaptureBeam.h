#ifndef _CAPTUREBEAM_H
#define _CAPTUREBEAM_H 

#include "AnimatedTexture.h"

// using namespace Ather;

class CaptureBeam : public AnimatedTexture
{
private:
	float kTotalCaptureTime; 
	float kCaptureTimer;

private: 
	void RunAnimation(); 

public:
	CaptureBeam();
	~CaptureBeam();

	void ResetAnimation(); 
	virtual void Render();
};

#endif 