#include "Texture.h"

Texture::Texture(std::string path)
{
	kGraphics = Graphics::Instance(); 
	kTex = kGraphics->LoadTexture(path); 

}

Texture::~Texture()
{
	SDL_DestroyTexture(kTex); 
	kTex = NULL; 
	kGraphics = NULL; 
}

void Texture::Render() 
{
	kGraphics->DrawTexture(kTex); 
}