#include "SoundBuffer.h"

#include <assert.h>

using ce::SoundBuffer;

SoundBuffer::SoundBuffer()
{
	soundBuffer = new sf::SoundBuffer();
}


SoundBuffer::~SoundBuffer()
{
	delete soundBuffer;
}


void SoundBuffer::LoadResource(const std::string path)
{
	this->path = path;

	if (!soundBuffer->loadFromFile(path))
	{
		assert("Couldn't load sound file!");
	}
}


sf::SoundBuffer* SoundBuffer::GetSoundBuffer() const
{
	return soundBuffer;
}