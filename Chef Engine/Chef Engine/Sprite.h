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


#pragma once
#include "DrawableComponent.h"

#include "Vec2.h"
#include "LuaBridgeBinder.h"

#include <string>

namespace sf
{
    class Sprite;
    class Color;
}

namespace ce
{
    class Transform;
    class Texture;

    ////////////////////////////////////////////////////////////
    /// \brief Component that gives your objects a visual representation
    /// Add a Sprite to a GameObject with GameObject:AddSprite()
    /// \code
    /// --Creates a GameObject and adds a Sprite to it
    ///
    /// object = Chef.GameObject("name")
    ///
    /// sprite = object:AddSprite() 
    /// \endcode
    /// 
    /// \n Tries to get a Sprite from a GameObject with GameObject:GetSprite()
    /// \code
    /// --Gets a Sprite from the GameObject "object"
    ///
    /// sprite = object:GetSprite()
    /// \endcode
    ///
    /// \n Remove a Sprite from a GameObject with GameObject:RemoveSprite()
    /// \code
    /// --Tries to remove a Sprite from the GameObject "object"
    ///
    /// object:RemoveSprite()
    /// \endcode
    ////////////////////////////////////////////////////////////
	class Sprite : public DrawableComponent
	{
        // Befriends the templated Bind function so it can access our protected functions
        friend void LuaBridgeBinder::Bind<ce::Sprite>(lua_State*);

	public:

        ////////////////////////////////////////////////////////////
        /// \brief Default Sprite Constructor. 
        /// In Lua you use GameObject:AddSprite()
        /// \code
        /// --Creates a GameObject and adds a Sprite to it
        ///
        /// object = Chef.GameObject("name")
        ///
        /// sprite = object:AddSprite() 
        /// \endcode
        ////////////////////////////////////////////////////////////
		Sprite();
		Sprite(const int drawOrder);
		~Sprite();

		void Update() override;

		#pragma region Origin Methods
        void SetOrigin(const float x, const float y);
		void SetOrigin(const sf::Vector2f newOrigin);
        
        const ce::Vec2f& GetOrigin() const;
		#pragma endregion

		#pragma region Color Methods
        void SetColor(const sf::Color& color);
		void SetColor(const int r, const int g, const int b, const int a);
		
        sf::Color GetColor() const;
		#pragma endregion

        void SetSprite(const std::string &fileName);

        void ChangeSprite(sf::Sprite* sprite);

		sf::Sprite* GetSprite() const;

		sf::Drawable* GetDrawable() const;

	private:
		friend class DrawEventManager;

		sf::Sprite* sprite;
		ce::Texture* texture;

        ////////////////////////////////////////////////////////////
        /// \brief Tints the Sprite in a specified Color
        /// \code
        /// -- Sets the Color of the Sprite to be blue
        ///
        /// sprite.color = Chef.Color(0, 0, 255, 255)
        /// \endcode
        ////////////////////////////////////////////////////////////
		sf::Color* color;
        /// \brief How far up the Sprite is drawn in the game, the higher the number, the higer it is drawn
		//int drawOrder;

		// Binds parts of this script to Lua
		static void DoBind(lua_State* L); 
	};
}