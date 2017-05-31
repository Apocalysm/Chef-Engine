#pragma once
#include "SoundBuffer.h"
#include "LuaBridgeBinder.h"

#include <string>

namespace ce
{
	class SoundManager
	{
		friend void LuaBridgeBinder::Bind<ce::SoundManager>(lua_State*);

	public:
		SoundManager(std::string fileName);
		~SoundManager();


		void PlaySFX();
		void SetSoundVolume(float volume);
		float GetSoundVolume() const;

		void SetMasterVolume(float volume);
		float GetMasterVolume() const;

	private:
		static void DoBind(lua_State* L);

		std::vector<sf::Sound*> sounds;
		std::string fileName;
		ce::SoundBuffer* buffer;

		static float sfxMasterVolume;

		float sfxVolume;

	};
}