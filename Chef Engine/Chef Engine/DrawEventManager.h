#pragma once
#include "TileMapLayer.h"

#include <SFML/Graphics.hpp>

#include <vector>
#include <map>

namespace ce
{
	class DrawableComponent;

	class DrawEventManager
	{
	public:
        static void AddDrawable(DrawableComponent* drawable);
		static void RemoveDrawable(DrawableComponent* drawable);
        static void MoveDrawable(DrawableComponent* drawable, int newDrawOrder);
		static void AddTmxLayers(std::vector<std::map<int, ce::TileMapLayer*>> tileMapLayers);
		void Draw(sf::RenderWindow& window);

	private:
        typedef unsigned long long uint64;

		typedef std::map<uint64, DrawableComponent*> DrawableMap;
		typedef std::map<uint64, DrawableMap> OrderDrawableMap;

		// OrderDrawableMap with DrawableComponents recently created
		static OrderDrawableMap enumToMapNewDrawable;

		// Map with DrawableComponents
		static OrderDrawableMap enumToMapDrawable;

		// Vector containing layers from Tiled to be drawn
        static std::vector<std::map<int, ce::TileMapLayer*>> tileMapLayers;
		
        static std::vector<sf::RenderStates> renderStates;
	};
}