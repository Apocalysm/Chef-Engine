#include "SoundManager.h"
#include "ResourceManager.h"

#include <assert.h>
#include <iostream>


float ce::SoundManager::sfxVolume;

ce::SoundManager::SoundManager(std::string fileName) :
	sound(new sf::Sound()), fileName(fileName)
{
	sfxVolume = 1;
	buffer = (ce::SoundBuffer*) ce::ResourceManager::GetResource(fileName);
	this->sound->setBuffer(*buffer->GetSoundBuffer());
}


ce::SoundManager::~SoundManager()
{

}


void ce::SoundManager::PlayMusic(const std::string fileName, bool loop)
{
	if (!music.openFromFile(fileName))
	{
		assert(!"Couldnt load file");
	}
	music.setLoop(loop);
	music.setVolume(musicVolume);
	music.play();
}



void ce::SoundManager::PlaySFX(const std::string fileName, sf::Sound* sound)
{
	buffer = (ce::SoundBuffer*) ce::ResourceManager::GetResource(fileName);

	sound->setBuffer(*buffer->GetSoundBuffer());
	sound->setVolume(sfxVolume);
	sound->play();

	
}

void ce::SoundManager::PlaySFXSOUND()
{
	sound->setVolume(sfxVolume);
	sound->play();
}

void ce::SoundManager::SetSFXVolume(float volume)
{
	sfxVolume = volume;
}

float ce::SoundManager::GetSFXVolume()
{
	return sfxVolume;
}

void ce::SoundManager::SetMusicVolume(float volume)
{
	musicVolume = volume;
}

float ce::SoundManager::GetMusicVolume()
{
	return musicVolume;
}

