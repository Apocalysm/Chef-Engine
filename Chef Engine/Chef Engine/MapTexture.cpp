#include "MapTexture.h"

using ce::MapTexture;

MapTexture::MapTexture(sf::VertexArray* vertex, const sf::Texture& texture) 
{
	vertex_array = va;
	this->texture = &texture;
}


MapTexture::~MapTexture()
{
	//delete texture;
	delete vertex_array;
}

sf::VertexArray& MapTexture::GetVertexArray()
{
	return *vertex_array;
}

void MapTexture::SetVertexArray(sf::VertexArray& vertex_array)
{
	this->vertex_array = &vertex_array;
}

const sf::Texture& MapTexture::GetTexture() const
{
	return *texture;
}

void MapTexture::SetTexture(const sf::Texture & texture)
{
	this->texture = &texture;
}


