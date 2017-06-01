#pragma once
#include "LuaBridgeBinder.h"

#include <string>

namespace sf
{
	class Music;
}

namespace ce
{
	class MusicManager
	{
		friend void LuaBridgeBinder::Bind<ce::MusicManager>(lua_State*);
	public:
		MusicManager();
		~MusicManager();

		void PlayMusic(const std::string& fileName, bool loop);
		void SetVolume(float volume);
		float GetVolume() const;

	private:
        sf::Music* music;

		static void DoBind(lua_State* L);
		float volume;
	};
}

