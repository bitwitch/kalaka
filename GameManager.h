#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

#include "AnimatedTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "ScreenManager.h"

class GameManager 
{
private: 

	static GameManager* sInstance; 
	const int FRAME_RATE = 60; 

	AssetManager* kAssetManager; 
	
	AudioManager* kAudioManager; 

	InputManager* kInputManager; 

	ScreenManager* kScreenManager; 

	bool      kQuit;
	Graphics* kGraphics; 
	Timer*    kTimer; 
	SDL_Event kEvents; 

public: 

	static GameManager* Instance(); 
	static void Release(); 

	void Run(); 

private: 

	GameManager(); 
	~GameManager();

	void EarlyUpdate(); 
	void Update(); 
	void Render(); 
	void LateUpdate(); 
};

#endif
