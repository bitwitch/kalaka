#include "Texture.h"

Texture::Texture(std::string filename)
{
	kGraphics = Graphics::Instance(); 
	kTex = AssetManager::Instance()->GetTexture(filename); 

	SDL_QueryTexture(kTex, NULL, NULL, &kWidth, &kHeight);

	kRenderRect.w = kWidth; 
	kRenderRect.h = kHeight; 
	kClipped = false; 
}

Texture::Texture(std::string filename, int x, int y, int w, int h)
{
	kGraphics = Graphics::Instance(); 
	kTex = AssetManager::Instance()->GetTexture(filename); 

	kClipped = true; 

	kWidth   = w; 
	kHeight  = h;

	kRenderRect.w = kWidth; 
	kRenderRect.h = kHeight; 

	kClipRect.x = x; 
	kClipRect.y = y; 
	kClipRect.w = kWidth; 
	kClipRect.h = kHeight; 
}

Texture::Texture(std::string text, std::string fontpath, int size, SDL_Color color)
{
	kGraphics = Graphics::Instance(); 
	kTex = AssetManager::Instance()->GetText(text, fontpath, size, color); 

	kClipped = false; 
	SDL_QueryTexture(kTex, NULL, NULL, &kWidth, &kHeight);

	kRenderRect.w = kWidth; 
	kRenderRect.h = kHeight; 
}

Texture::~Texture()
{
	kTex = NULL; 
	kGraphics = NULL; 
}

void Texture::Render() 
{
	Vector2 pos = Pos(world); 
	Vector2 scale = Scale(world); 

	kRenderRect.x = (int)(pos.x - kWidth * scale.x * 0.5f);
	kRenderRect.y = (int)(pos.y - kHeight * scale.x * 0.5f);
	kRenderRect.w = (int)(kWidth * scale.x);
	kRenderRect.h = (int)(kHeight * scale.y);

	kGraphics->DrawTexture(kTex, kClipped ? &kClipRect : NULL, &kRenderRect, Rotation(world)); 
}
