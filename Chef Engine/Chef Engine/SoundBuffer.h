#pragma once

#include "Resource.h"

#include <SFML\Audio.hpp>

namespace ce
{
	class SoundBuffer : public Resource
	{
	public:
		SoundBuffer();
		~SoundBuffer();

		void LoadResource(const std::string path);
		sf::SoundBuffer* GetSoundBuffer() const;

	private:
		sf::SoundBuffer* soundBuffer;
	};
}