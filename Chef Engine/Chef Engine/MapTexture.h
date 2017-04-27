#pragma once

#include <SFML\Graphics\VertexArray.hpp>
#include <SFML\Graphics\Texture.hpp>

class MapTexture
{
public:
	MapTexture(const sf::VertexArray& va, const sf::Texture& texture);
	~MapTexture();

	sf::VertexArray GetVertexArray() const;
	void SetVertexArray(const sf::VertexArray& va);

	sf::Texture GetTexture() const;
	void SetTexture(const sf::Texture& txt);

private:
	sf::VertexArray* vertex_array;
	sf::Texture* texture;
};

