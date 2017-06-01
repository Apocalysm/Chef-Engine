////////////////////////////////////////////////////////////
//
// Chef Engine
// Copyright (C) 2017 Oskar Svensson
//  
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//
// Author: Dennis Karlsson
//
////////////////////////////////////////////////////////////


#include "Text.h"
#include "GameObject.h"
#include "Font.h"
#include "Transform.h"
#include "DrawEventManager.h"
#include "ResourceManager.h"
#include "LuaBind.h"

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
	text->setPosition(transform->GetPosition().ToSfVector2());
	text->setRotation(transform->GetRotation());
	text->setScale(transform->GetScale().ToSfVector2());
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