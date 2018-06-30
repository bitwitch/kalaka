#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H

#include <SDL2/SDL.h>
#include <string.h>
#include "MathHelper.h"

class InputManager 
{
public:
	enum MOUSE_BUTTON { left=0, right, middle, back, forward };

private: 
	static InputManager* sInstance; 

	Uint8* kPrevKeyState;
	const Uint8* kKeyboardState;
	const Uint8* kKeyboardStates; 

	Uint32 kPrevMouseState; 
	Uint32 kMouseState; 

	int kMouseX; 
	int kMouseY; 

public: 
	static InputManager* Instance(); 
	static void Release(); 

	bool KeyDown(SDL_Scancode scanCode); 
	bool KeyPressed(SDL_Scancode scanCode); 
	bool KeyReleased(SDL_Scancode scanCode); 

	bool MouseButtonDown(MOUSE_BUTTON button);
	bool MouseButtonPressed(MOUSE_BUTTON button);
	bool MouseButtonReleased(MOUSE_BUTTON button);
	Vector2 MousePos(); 

	void Update(); 
	void UpdatePrevInput(); 
	
private: 
	InputManager(); 
	~InputManager(); 
}; 

#endif