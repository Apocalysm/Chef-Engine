#include "Font.h"

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

	font->loadFromFile(path);
}


sf::Font* ce::Font::GetFont() const
{
	return font;
}
