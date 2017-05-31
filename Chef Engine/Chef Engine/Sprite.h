#pragma once

#include "DrawableComponent.h"
#include "Component.h"
#include "Transform.h"
#include "LuaBridgeBinder.h"
#include "Texture.h"

namespace ce
{
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
        
        sf::Vector2f GetOrigin() const;	
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
		sf::Color color;
        /// \brief How far up the Sprite is drawn in the game, the higher the number, the higer it is drawn
		//int drawOrder;

		// Binds parts of this script to Lua
		static void DoBind(lua_State* L);
	};
}