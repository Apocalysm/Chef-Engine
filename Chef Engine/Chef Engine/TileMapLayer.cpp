#include "TileMapLayer.h"

using ce::TileMapLayer;

TileMapLayer::TileMapLayer(sf::VertexArray* vertexArray, const sf::Texture& texture)
{
	this->vertexArray = vertexArray;
	this->texture = &texture;
}


TileMapLayer::~TileMapLayer()
{
	delete vertexArray;
}


sf::VertexArray& TileMapLayer::GetVertexArray()
{
	return *vertexArray;
}


void TileMapLayer::SetVertexArray(sf::VertexArray& vertexArray)
{
	this->vertexArray = &vertexArray;
}


const sf::Texture& TileMapLayer::GetTexture() const
{
	return *texture;
}


void TileMapLayer::SetTexture(const sf::Texture & texture)
{
	this->texture = &texture;
}


