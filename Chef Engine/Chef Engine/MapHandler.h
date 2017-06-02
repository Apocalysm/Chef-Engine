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
// Author: Rasmus Andersson
//
////////////////////////////////////////////////////////////

#pragma once
#include "Vec2.h"
#include "LuaBridgeBinder.h"
#include "TileMapLayer.h"

#include <vector>
#include <map>
#include <string>
#include <cassert>
#include <array>

struct lua_State;

namespace sf
{
    class Texture;
    class RenderStates;
}

namespace Tmx
{
    class Map;
    class ObjectGroup;
    class Object;
    class Tileset;
    class TileLayer;
    class Image;
    struct MapTile;
    class Tile;
    class Color;
}

namespace ce
{
    class GameObject;

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
		static ce::Vec2i GetMapSize();

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

