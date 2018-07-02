#include "BackgroundStars.h"

BackgroundStars* BackgroundStars::sInstance = NULL; 

BackgroundStars* BackgroundStars::Instance()
{
	if (sInstance == NULL)
		sInstance = new BackgroundStars(); 
	return sInstance; 
}

void BackgroundStars::Release()
{
	delete sInstance; 
	sInstance = NULL; 
}

BackgroundStars::BackgroundStars()
{
	for (int i=0; i<LAYER_COUNT; i++)
	{
		kLayers[i] = new StarLayer(i); 
	}
}

BackgroundStars::~BackgroundStars()
{
	for (int i=0; i<LAYER_COUNT; i++)
	{
		delete kLayers[i]; 
		kLayers[i] = NULL; 
	}
}

// sets scroll to true for all stars
void BackgroundStars::Scroll(bool b)
{
	Star::Scroll(b); 
}

void BackgroundStars::Update()
{
	for (int i=0; i<LAYER_COUNT; i++)
		kLayers[i]->Update();
}

void BackgroundStars::Render()
{
	for (int i=0; i<LAYER_COUNT; i++)
		kLayers[i]->Render();
}

