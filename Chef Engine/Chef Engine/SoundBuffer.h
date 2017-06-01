#pragma once
#include "Resource.h"
#include <string>

namespace sf
{
    class SoundBuffer;
}

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