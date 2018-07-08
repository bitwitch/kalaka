#include "Formation.h"

Formation::Formation()
{
	kTimer = Timer::Instance(); 

	kOffsetAmount = 10.0f; 
	kOffsetDelay = 0.4f; 
	kOffsetTimer = 0.0f; 
	kOffsetCounter = 4;
	kOffsetDirection = 1; 

	kSpreadTimer = 0.0f; 
	kSpreadDelay = 0.6f; 
	kSpreadCounter = 0; 
	kSpreadDirection = 1; 

	kLocked = false; 

	kGridSize = Vector2(32.0f, 64.0f);
}

Formation::~Formation()
{
	kTimer = NULL; 
}

Vector2 Formation::GridSize()
{
	return kGridSize;
}

int Formation::GetTick()
{
	return (!kLocked || kOffsetCounter != 4)
		? kOffsetCounter 
		: kSpreadCounter;
}

void Formation::Lock()
{
	kLocked = true; 
}

bool Formation::Locked()
{
	return kLocked && kOffsetCounter == 4; 
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
				kOffsetDirection *= -1;
			}

			kOffsetTimer = 0.0f;
		}
	}
	else 
	{
		kSpreadTimer += kTimer->DeltaTime(); 

		if (kSpreadTimer >= kSpreadDelay)
		{
			kSpreadCounter += kSpreadDirection;
			kGridSize.x += kSpreadDirection * ((kSpreadCounter % 2) == 0 ? 1 : 2);

			if (kSpreadCounter == 4 || kSpreadCounter == 0)
				kSpreadDirection *= -1;

			kSpreadTimer = 0.0f; 
		}

	}
}
