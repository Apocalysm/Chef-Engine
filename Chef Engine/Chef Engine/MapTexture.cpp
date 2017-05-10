#include "MapTexture.h"

using ce::MapTexture;

MapTexture::MapTexture(sf::VertexArray* vertexArray, const sf::Texture& texture)
{
	this->vertexArray = vertexArray;
	this->texture = &texture;
}


MapTexture::~MapTexture()
{
	delete vertexArray;
}

sf::VertexArray& MapTexture::GetVertexArray()
{
	return *vertexArray;
}

void MapTexture::SetVertexArray(sf::VertexArray& vertexArray)
{
	this->vertexArray = &vertexArray;
}

const sf::Texture& MapTexture::GetTexture() const
{
	return *texture;
}

void MapTexture::SetTexture(const sf::Texture & texture)
{
	this->texture = &texture;
}


