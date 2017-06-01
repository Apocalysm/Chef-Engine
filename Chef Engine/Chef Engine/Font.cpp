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
