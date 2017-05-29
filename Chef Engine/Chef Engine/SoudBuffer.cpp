#include "SoudBuffer.h"

using ce::SoudBuffer;

SoudBuffer::SoudBuffer()
{
	soundBuffer = new sf::SoundBuffer();
}


SoudBuffer::~SoudBuffer()
{
	delete soundBuffer;
}


void SoudBuffer::LoadResource(const std::string path)
{
	this->path = path;

	soundBuffer->loadFromFile(path);
}


sf::SoundBuffer* SoudBuffer::GetSoundBuffer() const
{
	return soundBuffer;
}