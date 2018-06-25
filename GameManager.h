#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

#include "Texture.h"
#include "Timer.h"

class GameManager 
{
private: 

	static GameManager* sInstance; 

	const int FRAME_RATE = 60; 

	bool      kQuit;
	Graphics* kGraphics; 
	Timer*    kTimer; 
	SDL_Event kEvents; 
	Texture*  kTex; 

public: 

	static GameManager* Instance(); 
	static void Release(); 

	void Run(); 

private: 

	GameManager(); 
	~GameManager();
};

#endif
