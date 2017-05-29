#pragma once
#include<SFML\Audio.hpp>
#include <cstring>

namespace ce
{
	class SoundManager
	{
	public:
		SoundManager();
		~SoundManager();

		void PlayMusic(const std::string fileName, bool loop);
		void SetMusicVolume(int volume);

		void PlaySFX(const std::string fileName, sf::Sound* sound);
		void SetSFXVolume(float volume);


	private:
		sf::Music music;
		//sf::Sound sound;
		sf::SoundBuffer buffer;

	};
}