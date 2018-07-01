#include "AudioManager.h"
#define AUDIOT_FREQUENCY 44100
#define AUDIOT_CHUNKSIZE  4096

AudioManager* AudioManager::sInstance = NULL; 

AudioManager* AudioManager::Instance()
{
	if (sInstance == NULL)
		sInstance = new AudioManager(); 
	return sInstance; 
}

void AudioManager::Release()
{
	delete sInstance; 
	sInstance = NULL; 
}

AudioManager::AudioManager() 
{
	kAssetManager = AssetManager::Instance(); 

	if (Mix_OpenAudio(AUDIOT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, AUDIOT_CHUNKSIZE) < 0)
		printf("Mixer Initialization Error: %s\n", Mix_GetError()); 
}

AudioManager::~AudioManager() 
{
	kAssetManager = NULL; 
	Mix_Quit(); 
}

void AudioManager::PlayMusic(std::string filename, int loops) 
{
	Mix_PlayMusic(kAssetManager->GetMusic(filename), loops); 
}

void AudioManager::PauseMusic()
{
	if (Mix_PlayingMusic() != 0)
		Mix_PauseMusic();
}

void AudioManager::ResumeMusic()
{
	if (Mix_PausedMusic() != 0)
		Mix_ResumeMusic(); 
}

void AudioManager::PlaySFX(std::string filename, int loops, int channel)
{
	Mix_PlayChannel(channel, kAssetManager->GetSFX(filename), loops); 
}
