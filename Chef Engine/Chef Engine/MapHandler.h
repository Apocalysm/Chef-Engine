#pragma once
#include"LuaBridgeBinder.h"
#include "TileMapLayer.h"
#include "GameObject.h"

#include <Tmx\TmxMap.h>
#include <Tmx\TmxObjectGroup.h>
#include <Tmx\TmxObject.h>
#include <Tmx\TmxTileset.h>
#include <Tmx\TmxTileLayer.h>
#include <Tmx\TmxImage.h>
#include <Tmx\TmxTile.h>
#include <Tmx\TmxMapTile.h>
#include <Tmx\TmxColor.h>

#include <SFML\Graphics.hpp>

#include <vector>
#include <map>
#include <string>
#include <cassert>
#include <array>

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
		static sf::Vector2i GetMapSize();

		std::vector<std::string*> tileMapNames;

	private:
		static void DoBind(lua_State* L);

		static int mapHeight;
		static int mapWidth;
		static int tileHeight;
		static int tileWidth;
		
		std::vector<Tmx::Tileset*> tileSets;
		std::vector<Tmx::TileLayer*> tileLayers;
		std::vector<ce::GameObject*> gameObjects;
		std::vector<sf::Texture> tileTextures;

		std::vector<std::map<int, TileMapLayer*>> tileMapLayers;
		
		std::vector<sf::RenderStates*> states;
		Tmx::Map* map;

	};
}

