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

	class Text : public DrawableComponent
	{
		// Befriends the templated Bind function so it can access our protected functions
		friend void LuaBridgeBinder::Bind<ce::Text>(lua_State*);

	public:
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