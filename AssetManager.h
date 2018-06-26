#ifndef _ASSETMANAGER_H
#define _ASSETMANAGER_H

#include "Graphics.h"
#include <map> 

class AssetManager 
{
private:

	static AssetManager* sInstance; 
	std::map<std::string, SDL_Texture*> kTextures;

public: 

	static AssetManager* Instance(); 
	static void Release();
	SDL_Texture* GetTexture(std::string filename); 

private: 
	AssetManager();
	~AssetManager(); 
}; 
#endif