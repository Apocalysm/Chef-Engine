#pragma once
#include <map>
#include <SFML/Graphics.hpp>

namespace ce
{
	class Sprite;

	class DrawEventManager
	{
	public:
		DrawEventManager();

		void AddSprite(Sprite* sprite);
		void RemoveSprite(Sprite* sprite);
		void Draw(sf::RenderWindow& window);

	private:
		typedef std::map<int, Sprite*> SpriteMap;
		typedef std::map<int, SpriteMap> OrderSpriteMap;

		// OrderSpriteMap with Sprite components recently created
		OrderSpriteMap enumToMapNewSpr;

		// Map with Sprite componenets
		OrderSpriteMap enumToMapSpr;
	};
}