#pragma once
#include <Tmx\TmxMap.h>
#include <Tmx\TmxObjectGroup.h>
#include <Tmx\TmxObject.h>
#include <Tmx\TmxTileset.h>
#include <Tmx\TmxTileLayer.h>
#include <Tmx\TmxImage.h>
#include <Tmx\TmxTile.h>
#include <Tmx\TmxMapTile.h>
#include <Tmx\TmxColor.h>

#include"LuaBridgeBinder.h"
#include "TileMapLayer.h"

#include <vector>
#include <map>
#include <string>
#include <cassert>
#include <array>

#include <SFML\Graphics.hpp>

namespace ce
{
	class MapHandler
	{
		friend void LuaBridgeBinder::Bind<ce::MapHandler>(lua_State*);

	public:
		MapHandler();
		~MapHandler();

		void LoadMapIndex(const int mapIndex);
		void LoadMap(const std::string& fileName);
		void RegisterMap(int index, std::string* mapName);
		virtual void LoadObject();

		std::vector<std::string*> tileMapNames;

	private:
		static void DoBind(lua_State* L);

		int mapHeight;
		int mapWidth;
		int tileHeight;
		int tileWidth;
		
		std::vector<Tmx::Tileset*> tileSets;
		std::vector<sf::Texture> tileTextures;
		std::vector<Tmx::TileLayer*> tileLayers;

		std::vector<std::map<int, TileMapLayer*>> tileMapLayers;
		
		std::vector<sf::RenderStates*> states;
		Tmx::Map* map;

	};
}

