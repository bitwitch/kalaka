#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"

class GameManager 
{
private: 

	static GameManager* sInstance; 
	const int FRAME_RATE = 60; 

	AssetManager* kAssetManager; 
	InputManager* kInputManager; 
	AudioManager* kAudioManager; 

	bool      kQuit;
	Graphics* kGraphics; 
	Timer*    kTimer; 
	SDL_Event kEvents; 

	Texture*  kTex;  
	Texture*  kTexEvil;  

public: 

	static GameManager* Instance(); 
	static void Release(); 

	void Run(); 

private: 

	GameManager(); 
	~GameManager();
};

#endif
