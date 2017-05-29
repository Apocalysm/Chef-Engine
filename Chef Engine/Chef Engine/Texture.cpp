#include "Texture.h"

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

	texture->loadFromFile(path);
}


sf::Texture* Texture::GetTexture() const
{
	return texture;
}
