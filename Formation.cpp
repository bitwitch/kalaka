#include "Formation.h"

Formation::Formation()
{
	kTimer = Timer::Instance(); 

	kOffsetAmount = 30.0f; 
	kOffsetDelay = 1.0f; 
	kOffsetTimer = 0.0f; 
	kOffsetCounter = 4;
	kOffsetDirection = 1; 

	kSpreadTimer = 0.0f; 
	kSpreadDelay = 1.0f; 
	kSpreadCounter = 0; 
	kSpreadDirection = 1; 

	kLocked = false; 

	kGridSize = Vector2(50.0f, 80.0f);
}

Formation::~Formation()
{
	kTimer = NULL; 
}

Vector2 Formation::GridSize()
{
	return kGridSize;
}

void Formation::Lock()
{
	kLocked = true; 
}

void Formation::Update()
{
	if (!kLocked || kOffsetCounter != 4)
	{
		kOffsetTimer += kTimer->DeltaTime(); 
		if (kOffsetTimer >= kOffsetDelay)
		{	
			kOffsetCounter++;
			Translate(VEC2_RIGHT * kOffsetDirection * kOffsetAmount, world);

			if (kOffsetCounter == 8)
			{
				kOffsetCounter = 0; 
				kOffsetDirection = -1;
			}

			kOffsetTimer = 0.0f;
		}
	}
}
