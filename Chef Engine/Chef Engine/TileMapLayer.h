#pragma once

#include <SFML\Graphics\VertexArray.hpp>
#include <SFML\Graphics\Texture.hpp>

namespace ce
{
	class TileMapLayer
	{
		public:
				TileMapLayer(sf::VertexArray* va, const sf::Texture& txt);
			~TileMapLayer();

				sf::VertexArray& GetVertexArray();
				void SetVertexArray(sf::VertexArray& vertexArray);

			const sf::Texture& GetTexture() const;
				void SetTexture(const sf::Texture& texture);

		private:
				sf::VertexArray* vertexArray;
			const sf::Texture* texture;
	};
}

