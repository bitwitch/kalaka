#ifndef _SCREENMANAGER_H
#define _SCREENMANAGER_H

#include "StartScreen.h"

class ScreenManager 
{
private: 
	enum SCREENS { start, play }; 
	static ScreenManager* sInstance; 

	InputManager* kInput; 

	BackgroundStars* kStars; 

	StartScreen* kStartScreen; 

	SCREENS kCurrentScreen;

public:
	static ScreenManager* Instance(); 
	static void Release(); 

	void Update(); 
	void Render();

private: 
	ScreenManager();
	~ScreenManager();
}; 

#endif 