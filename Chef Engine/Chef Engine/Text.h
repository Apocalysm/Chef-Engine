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


#pragma once
#include "DrawableComponent.h"

namespace sf
{
	class Text;
	class Font;
    class Color;
}

namespace ce
{
	class DrawableComponent;
	class Font;


    ////////////////////////////////////////////////////////////
    /// \brief Component that gives your texts a visual representation
    /// Add a Text to a GameObject with GameObject:AddText()
    /// \code
    /// --Creates a GameObject and adds a Text to it
    ///
    /// object = Chef.GameObject("name")
    ///
    /// sprite = object:AddText() 
    /// \endcode
    /// 
    /// \n Tries to get a Text from a GameObject with GameObject:GetText()
    /// \code
    /// --Gets a Text from the GameObject "object"
    ///
    /// text = object:GetText()
    /// \endcode
    ///
    /// \n Remove a Text from a GameObject with GameObject:RemoveText()
    /// \code
    /// --Tries to remove a Text from the GameObject "object"
    ///
    /// object:RemoveText()
    /// \endcode
    ////////////////////////////////////////////////////////////
	class Text : public DrawableComponent
	{
		// Befriends the templated Bind function so it can access our protected functions
		friend void LuaBridgeBinder::Bind<ce::Text>(lua_State*);

	public:
        ////////////////////////////////////////////////////////////
        /// \brief Default Text Constructor. 
        /// In Lua you use GameObject:AddText()
        /// \code
        /// --Creates a GameObject and adds a Text to it
        ///
        /// object = Chef.GameObject("name")
        ///
        /// sprite = object:AddText() 
        /// \endcode
        ////////////////////////////////////////////////////////////
		Text();
		~Text();

		void Update();

		sf::Drawable* GetDrawable() const;


		void SetFont(const std::string path);
		sf::Font* GetFont() const;

		void SetString(const std::string text);
		std::string GetString() const;

		void SetSize(const unsigned int size);
		unsigned int GetSize() const;

		void SetFillColor(const sf::Color& color);
		sf::Color GetFillColor() const;

		void SetOutlineColor(const sf::Color& color);
		sf::Color GetOutlineColor() const;

		void SetOutlineThickness(float thickness);
		float GetOutlineThickness() const;

	private:
		sf::Text* text;
		ce::Font* font;

		// Binds parts of this script to Lua
		static void DoBind(lua_State* L);
	};
}