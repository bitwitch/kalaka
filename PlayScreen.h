#ifndef _PLAYSCREEN_H
#define _PLAYSCREEN_H

#include "InputManager.h"
#include "BackgroundStars.h"
#include "PlayHUD.h"

class PlayScreen : public GameEntity
{
private: 
	Timer* kTimer; 
	InputManager* kInput; 
	BackgroundStars* kStars;
	PlayHUD* kPlayHUD;

public: 
	PlayScreen();
	~PlayScreen();

	void Update(); 
	void Render(); 
};

#endif