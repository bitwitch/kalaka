#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "GameEntity.h"
#include "Graphics.h"

class Texture : public GameEntity
{
private:

	SDL_Texture* kTex; 
	Graphics* kGraphics; 

public:

	Texture(std::string path); 
	~Texture();

	virtual void Render(); 
};

#endif