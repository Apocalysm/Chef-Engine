#pragma once
#include "MapTexture.h"

#include <SFML/Graphics.hpp>

#include <vector>
#include <map>


namespace ce
{
	class Sprite;

	class DrawEventManager
	{
	public:
		DrawEventManager();

        static void AddSprite(Sprite* sprite);
		static void RemoveSprite(Sprite* sprite);
		static void AddTmxLayers(std::vector<std::map<int, ce::MapTexture*>> tileMapLayers);
		void Draw(sf::RenderWindow& window);

	private:
        typedef unsigned long long int64;

		typedef std::map<int64, Sprite*> SpriteMap;
		typedef std::map<int64, SpriteMap> OrderSpriteMap;

		// OrderSpriteMap with Sprite components recently created
		static OrderSpriteMap enumToMapNewSpr;

		// Map with Sprite components
		static OrderSpriteMap enumToMapSpr;

		// Vector containing layers from Tiled to be drawn
        static std::vector<std::map<int, ce::MapTexture*>> m_tileMapLayers;
		
        static std::vector<sf::RenderStates> renderStates;
	};
}