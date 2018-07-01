#include "AssetManager.h"

AssetManager* AssetManager::sInstance = NULL; 

AssetManager* AssetManager::Instance()
{
	if (sInstance == NULL)
		sInstance = new AssetManager(); 
	return sInstance; 
}

void AssetManager::Release()
{
	delete sInstance; 
	sInstance = NULL;
}

AssetManager::AssetManager() {}

AssetManager::~AssetManager() 
{	
	// clear textures
	for (auto tex : kTextures)
	{
		if (tex.second != NULL)
		{
			SDL_DestroyTexture(tex.second);
		}
	}
	kTextures.clear(); 

	// clear texts
	for (auto text : kTexts)
	{
		if (text.second != NULL)
		{
			SDL_DestroyTexture(text.second);
		}
	}
	kTexts.clear(); 

	// clear fonts
	for (auto font : kFonts)
	{
		if (font.second != NULL)
		{
			TTF_CloseFont(font.second);
		}
	}
	kFonts.clear(); 
}

// Cache Textures
SDL_Texture* AssetManager::GetTexture(std::string filename)
{
	std::string fullpath = SDL_GetBasePath(); 
	fullpath.append("assets/" + filename);

	if (kTextures[fullpath] == nullptr)
		kTextures[fullpath] = Graphics::Instance()->LoadTexture(fullpath); 

	return kTextures[fullpath]; 
}

// Cache Fonts
TTF_Font* AssetManager::GetFont(std::string filename, int size)
{
	std::string fullpath = SDL_GetBasePath(); 
	fullpath.append("assets/" + filename);
	std::string key = fullpath + (char)size; 
	if (kFonts[key] == nullptr)
	{
		kFonts[key] = TTF_OpenFont(fullpath.c_str(), size);
		if (kFonts[key] == nullptr)
			printf("Font Loading Error: Font-%s Error-$s\n", filename.c_str(), TTF_GetError());
	}

	return kFonts[key]; 
}

// Cache Texts
SDL_Texture* AssetManager::GetText(std::string text, std::string filename, int size, SDL_Color color)
{
	TTF_Font* font = GetFont(filename, size);
	std::string key = text + filename + (char)size + (char)(color.r) + (char)(color.g) + (char)(color.b) + (char)(color.a);

	if (kTexts[key] == nullptr)
		kTexts[key] = Graphics::Instance()->CreateTextTexture(font, text, color); 

	return kTexts[key]; 
} 

Mix_Music* AssetManager::GetMusic(std::string filename)
{
	std::string fullpath = SDL_GetBasePath(); 
	fullpath.append("assets/" + filename);

	if (kMusic[fullpath] == nullptr)
	{
		kMusic[fullpath] = Mix_LoadMUS(fullpath.c_str()); 
		if (kMusic[fullpath] == nullptr)
			printf("Music Loading Error: File-%s Error-%s\n", filename.c_str(), Mix_GetError());	
	}

	return kMusic[fullpath]; 
}

Mix_Chunk* AssetManager::GetSFX(std::string filename)
{
	std::string fullpath = SDL_GetBasePath(); 
	fullpath.append("assets/" + filename);

	if (kSFX[fullpath] == nullptr)
	{
		kSFX[fullpath] = Mix_LoadWAV(fullpath.c_str()); 
		if (kSFX[fullpath] == nullptr)
			printf("Music Loading Error: File-%s Error-%s\n", filename.c_str(), Mix_GetError());	
	}

	return kSFX[fullpath]; 
}