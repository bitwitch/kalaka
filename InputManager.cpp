#include "InputManager.h"

InputManager* InputManager::sInstance = NULL; 

InputManager* InputManager::Instance()
{
	if (sInstance == NULL)
		sInstance = new InputManager(); 
	return sInstance; 
}

void InputManager::Release()
{
	delete sInstance; 
	sInstance = NULL; 
}

InputManager::InputManager() 
{
	kKeyboardState = SDL_GetKeyboardState(&kKeyLength);
	kPrevKeyboardState = new Uint8[kKeyLength]; 
	memcpy(kPrevKeyboardState, kKeyboardState, kKeyLength);
}

InputManager::~InputManager() 
{
	delete[] kPrevKeyboardState;
	kPrevKeyboardState = NULL; 
}

bool InputManager::KeyDown(SDL_Scancode scanCode)
{
	return kKeyboardState[scanCode]; 
}

bool InputManager::KeyPressed(SDL_Scancode scanCode)
{	
	return !kPrevKeyboardState[scanCode] && kKeyboardState[scanCode]; 
}

bool InputManager::KeyReleased(SDL_Scancode scanCode)
{	
	return kPrevKeyboardState[scanCode] && !kKeyboardState[scanCode]; 
}

Vector2 InputManager::MousePos() 
{
	return Vector2((float)kMouseX, (float)kMouseY);
}

bool InputManager::MouseButtonDown(MOUSE_BUTTON button) 
{	
	Uint32 mask = 0; 
	switch(button) 
	{
	case left: 
		mask = SDL_BUTTON_LMASK;
		break; 
	case right: 
		mask = SDL_BUTTON_RMASK;
		break; 
	case middle: 
		mask = SDL_BUTTON_MMASK;
		break; 
	case back: 
		mask = SDL_BUTTON_X1MASK;
		break; 
	case forward: 
		mask = SDL_BUTTON_X2MASK;
		break; 
	}

	return (kMouseState & mask); 
}

bool InputManager::MouseButtonPressed(MOUSE_BUTTON button) 
{	
	Uint32 mask = 0; 
	switch(button) 
	{
	case left: 
		mask = SDL_BUTTON_LMASK;
		break; 
	case right: 
		mask = SDL_BUTTON_RMASK;
		break; 
	case middle: 
		mask = SDL_BUTTON_MMASK;
		break; 
	case back: 
		mask = SDL_BUTTON_X1MASK;
		break; 
	case forward: 
		mask = SDL_BUTTON_X2MASK;
		break; 
	}

	return !(kPrevMouseState & mask) && (kMouseState & mask); 
}

bool InputManager::MouseButtonReleased(MOUSE_BUTTON button) 
{	
	Uint32 mask = 0; 
	switch(button) 
	{
	case left: 
		mask = SDL_BUTTON_LMASK;
		break; 
	case right: 
		mask = SDL_BUTTON_RMASK;
		break; 
	case middle: 
		mask = SDL_BUTTON_MMASK;
		break; 
	case back: 
		mask = SDL_BUTTON_X1MASK;
		break; 
	case forward: 
		mask = SDL_BUTTON_X2MASK;
		break; 
	}

	return (kPrevMouseState & mask) && !(kMouseState & mask); 
}


void InputManager::Update()
{
	kMouseState = SDL_GetMouseState(&kMouseX, &kMouseY); 
}

void InputManager::UpdatePrevInput()
{
	memcpy(kPrevKeyboardState, kKeyboardState, kKeyLength);
	kPrevMouseState = kMouseState; 
}