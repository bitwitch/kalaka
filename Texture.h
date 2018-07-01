#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "GameEntity.h"
#include "AssetManager.h"

class Texture : public GameEntity
{
protected:

	Graphics* kGraphics; 
	SDL_Texture* kTex; 

	int kWidth;
	int kHeight; 
	bool kClipped;

	SDL_Rect kRenderRect;
	SDL_Rect kClipRect; 

public:

	Texture(std::string filename); 
	Texture(std::string filename, int x, int y, int w, int h); 
	Texture(std::string text, std::string fontpath, int size, SDL_Color color); 
	~Texture();

	virtual void Render(); 
};

#endif