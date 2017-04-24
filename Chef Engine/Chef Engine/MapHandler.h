#pragma once
#include <Tmx\TmxMap.h>
#include <Tmx\TmxObjectGroup.h>
#include <Tmx\TmxObject.h>
#include <Tmx\TmxTileset.h>
#include <Tmx\TmxTileLayer.h>
#include <Tmx\TmxImage.h>
#include <Tmx\TmxTile.h>
#include <Tmx\TmxMapTile.h>

#include <vector>
#include <string>

#include <SFML\Graphics.hpp>

namespace ce
{
	class MapHandler
	{
	public:
		MapHandler();
		~MapHandler();

		void LoadMap(const std::string& fileName);
		void DrawMap(sf::RenderWindow window);

	private:
		int mapHeight;
		int mapWidth;
		int tileHeight;
		int tileWidth;
		std::vector<Tmx::TileLayer*> tileLayers;
		std::vector <sf::VertexArray*> vertexLayers;

		Tmx::Tileset* tileSet;
		Tmx::Map map;

	};
}

