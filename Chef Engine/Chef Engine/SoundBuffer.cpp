#include "SoundBuffer.h"

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

	soundBuffer->loadFromFile(path);
}


sf::SoundBuffer* SoundBuffer::GetSoundBuffer() const
{
	return soundBuffer;
}