#include "Texture.h"

#include <assert.h>

using ce::Texture;

Texture::Texture()
{
	texture = new sf::Texture();
}


Texture::~Texture()
{
	delete texture;
}


void Texture::LoadResource(const std::string path)
{
	this->path = path;

	if (!texture->loadFromFile(path))
	{
		assert(!"Couldn't load image file!");
	}
}


sf::Texture* Texture::GetTexture() const
{
	return texture;
}
