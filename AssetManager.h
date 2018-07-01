#ifndef _ASSETMANAGER_H
#define _ASSETMANAGER_H

#include "Graphics.h"
#include <map> 

class AssetManager 
{
private:

	static AssetManager* sInstance; 
	std::map<std::string, SDL_Texture*> kTextures;
	std::map<std::string, SDL_Texture*> kTexts;
	std::map<std::string, TTF_Font*> kFonts;

public: 

	static AssetManager* Instance(); 
	static void Release();

	SDL_Texture* GetTexture(std::string filename); 
	SDL_Texture* GetText(std::string text, std::string filename, int size, SDL_Color color); 

private: 
	AssetManager();
	~AssetManager(); 

	TTF_Font* GetFont(std::string filename, int size); 
}; 
#endif