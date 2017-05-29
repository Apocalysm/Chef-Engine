#pragma once

#include "Resource.h"

#include <SFML\Graphics.hpp>

namespace ce
{
	class Texture : public Resource
	{
	public:
		Texture();
		~Texture();

		void LoadResource(const std::string path);
		sf::Texture* GetTexture() const;

	private:
		sf::Texture* texture;
	};
}