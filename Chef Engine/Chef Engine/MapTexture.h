#pragma once

#include <SFML\Graphics\VertexArray.hpp>
#include <SFML\Graphics\Texture.hpp>

namespace ce
{
	class MapTexture
	{
	public:
		MapTexture(sf::VertexArray* va, const sf::Texture& txt);
		~MapTexture();

		sf::VertexArray& GetVertexArray();
		void SetVertexArray(sf::VertexArray& va);

		const sf::Texture& GetTexture() const;
		void SetTexture(const sf::Texture& txt);

	private:
		sf::VertexArray* vertex_array;
		const sf::Texture* texture;
	};
}

