#pragma once

#include "Resource.h"

#include <string>

namespace sf
{
	class Font;
}

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