#pragma once
#include "SoundBuffer.h"

#include <string>

namespace ce
{
	class SoundManager
	{
	public:
		SoundManager(std::string fileName);
		~SoundManager();

		void PlayMusic(const std::string fileName, bool loop);
		void SetMusicVolume(float volume);
		float GetMusicVolume();

		void PlaySFX(const std::string fileName, sf::Sound* sound);
		void PlaySFXSOUND();
		void SetSFXVolume(float volume);
		float GetSFXVolume();


	private:
		sf::Music music;
		sf::Sound* sound;
		std::string fileName;
		ce::SoundBuffer* buffer;
		static float sfxVolume;
		float musicVolume;

	};
}