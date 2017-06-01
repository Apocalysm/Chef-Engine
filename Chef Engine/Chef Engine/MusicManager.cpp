#include "MusicManager.h"

#include "LuaBind.h"

#include <SFML\Audio.hpp>

using namespace ce;

MusicManager::MusicManager() : volume(1)
{
}


MusicManager::~MusicManager()
{
}

void ce::MusicManager::PlayMusic(std::string fileName, bool loop)
{
	sf::Music music;
	//Load the music file
	if (!music.openFromFile(fileName))
	{

	}
	//Set the volume for the music
	music.setVolume(volume);
	//Play the music
	music.play();
}


//Setting the volume for the music
void ce::MusicManager::SetVolume(float volume)
{
	this->volume = volume;
}


//Get the volume for the music
float ce::MusicManager::GetVolume() const
{
	return volume;
}

void ce::MusicManager::DoBind(lua_State * L)
{
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Chef")
			.beginClass<MusicManager>("Sound")
				.addFunction("PlaySound", &MusicManager::PlayMusic)
				.addProperty("volume", &MusicManager::GetVolume, &MusicManager::SetVolume)
			.endClass()
		.endNamespace();
}
