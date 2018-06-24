#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

#include "Graphics.h"

class GameManager 
{
private: 

	static GameManager* sInstance; 

	bool kQuit;
	Graphics* kGraphics; 

	SDL_Event kEvents; 

public: 

	static GameManager* Instance(); 
	static void Release(); 

	void Run(); 

private: 

	GameManager(); 
	~GameManager();
};

#endif
