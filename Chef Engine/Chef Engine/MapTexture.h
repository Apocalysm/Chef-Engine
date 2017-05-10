#pragma once

#include <SFML\Graphics\VertexArray.hpp>
#include <SFML\Graphics\Texture.hpp>

namespace ce
{
    class MapTexture
    {
    public:
		MapTexture(sf::VertexArray* va, const sf::Texture& texture);
	    ~MapTexture();

		sf::VertexArray& GetVertexArray();
	    void SetVertexArray(sf::VertexArray& vertexArray);

	    const sf::Texture& GetTexture() const;
	    void SetTexture(const sf::Texture& texture);

    private:
	    sf::VertexArray* vertexArray;
	    const sf::Texture* texture;
    };
}

