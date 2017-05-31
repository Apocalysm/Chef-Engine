#include "Text.h"
#include "DrawEventManager.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Font.h"

#include <SFML\Graphics\Text.hpp>

using ce::Text;

Text::Text()
{
	text = new sf::Text();
}


Text::~Text()
{
	delete text;

	font->DecrementUseCount();
}


void ce::Text::Update()
{
	// Makes the texts transform the same as the gameObjects transform
	text->setPosition(transform->GetPosition());
	text->setRotation(transform->GetRotation());
	text->setScale(transform->GetScale());
}


sf::Drawable* ce::Text::GetDrawable() const
{
	return text;
}


void ce::Text::SetFont(const std::string path)
{
	// Gets the font from the resource manager
	font = (Font*)ResourceManager::GetResource(path);

	// Sets the font to the text object
	text->setFont(*font->GetFont());
}


sf::Font* ce::Text::GetFont() const
{
	return font->GetFont();
}


void ce::Text::SetString(const std::string string)
{
	text->setString(string);
}


std::string ce::Text::GetString() const
{
	return text->getString();
}


void ce::Text::SetSize(const unsigned int size)
{
	text->setCharacterSize(size);
}


unsigned int ce::Text::GetSize() const
{
	return text->getCharacterSize();
}


void ce::Text::SetFillColor(const sf::Color& color)
{
	text->setFillColor(color);
}


sf::Color ce::Text::GetFillColor() const
{
	return text->getFillColor();
}


void ce::Text::SetOutlineColor(const sf::Color& color)
{
	text->setOutlineColor(color);
}


sf::Color ce::Text::GetOutlineColor() const
{
	return text->getOutlineColor();
}


void ce::Text::SetOutlineThickness(float thickness)
{
	text->setOutlineThickness(thickness);
}


float ce::Text::GetOutlineThickness() const
{
	return text->getOutlineThickness();
}


void ce::Text::DoBind(lua_State * L)
{
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Chef")
			.deriveClass<Text, DrawableComponent>("Text")
				.addConstructor<void(*)(void)>()
				.addProperty("font", &Text::GetFont, &Text::SetFont)
				.addProperty("string", &Text::GetString, &Text::SetString)
				.addProperty("size", &Text::GetSize, &Text::SetSize)
				.addProperty("fillColor", &Text::GetFillColor, &Text::SetFillColor)
				.addProperty("outlineColor", &Text::GetOutlineColor, &Text::SetOutlineColor)
				.addProperty("outlineThickness", &Text::GetOutlineThickness, &Text::SetOutlineThickness)
			.endClass()
		.endNamespace();
}