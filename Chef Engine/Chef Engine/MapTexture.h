#pragma once

#include <SFML\Graphics\VertexArray.hpp>
#include <SFML\Graphics\Texture.hpp>

namespace ce
{
    class MapTexture
    {
    public:
        MapTexture(const sf::VertexArray* va, const sf::Texture& txt);
        ~MapTexture();

        const sf::VertexArray& GetVertexArray() const;
        void SetVertexArray(const sf::VertexArray& va);

        const sf::Texture& GetTexture() const;
        void SetTexture(const sf::Texture& txt);

    private:
        const sf::VertexArray* vertex_array;
        const sf::Texture* texture;
    };
}
