#include "Font.h"

#include <SFML\Graphics\Font.hpp>

#include <assert.h>

using ce::Font;

Font::Font()
{
	font = new sf::Font();
}


Font::~Font()
{
}


void ce::Font::LoadResource(const std::string path)
{
	this->path = path;

	if (!font->loadFromFile(path))
	{
		assert(!"Couldn't load font!");
	}
}


sf::Font* ce::Font::GetFont() const
{
	return font;
}
