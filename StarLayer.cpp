#include "StarLayer.h"

StarLayer::StarLayer(int layer)
{
	for (int i=0; i<STAR_COUNT; i++)
	{
		kStars[i] = new Star(layer); 
	}
}

StarLayer::~StarLayer()
{
	for (int i=0; i<STAR_COUNT; i++)
	{
		delete kStars[i];
		kStars[i] = NULL; 
	}
}

void StarLayer::Update()
{
	for (int i=0; i<STAR_COUNT; i++)
		kStars[i]->Update(); 
}

void StarLayer::Render()
{
	for (int i=0; i<STAR_COUNT; i++)
		kStars[i]->Render(); 
}

