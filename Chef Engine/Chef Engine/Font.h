#pragma once

#include "Resource.h"

#include <SFML\Graphics.hpp>

namespace ce
{
	class Font : public Resource
	{
	public:
		Font();
		~Font();

		void LoadResource(const std::string path);

		sf::Font* GetFont() const;

	private:
		sf::Font* font;
	};
}