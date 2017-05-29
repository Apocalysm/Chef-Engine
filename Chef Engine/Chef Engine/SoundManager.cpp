#include "SoundManager.h"
#include <assert.h>

ce::SoundManager::SoundManager()
{
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
	music.play();
}

void ce::SoundManager::SetMusicVolume(int volume)
{
	music.setVolume(volume);
}


void ce::SoundManager::PlaySFX(const std::string fileName, sf::Sound* sound)
{

	if (!buffer.loadFromFile(fileName))
	{
		assert(!"Couldnt load file");
	}

	sound->setBuffer(buffer);
	sound->play();
}

/*void ce::SoundManager::SetSFXVolume(float volume)
{
	sound.setVolume(volume);
}*/
