#pragma once

#include "Resource.h"

#include <SFML\Audio.hpp>

namespace ce
{
	class SoudBuffer : public Resource
	{
	public:
		SoudBuffer();
		~SoudBuffer();

		void LoadResource(const std::string path);
		sf::SoundBuffer* GetSoundBuffer() const;

	private:
		sf::SoundBuffer* soundBuffer;
	};
}