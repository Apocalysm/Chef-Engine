#pragma once

#include "MapHandler.h"
#include <iostream>
using ce::MapHandler;

MapHandler::MapHandler()
{
}


MapHandler::~MapHandler()
{
}

void ce::MapHandler::LoadMapIndex(const int mapIndex)
{
	std::string* mapString = tileMapNames[mapIndex];
	for (int i = 0; i < tileMapNames.size(); i++)
	{
		if (tileMapNames[i] == mapString)
		{
			LoadMap(*mapString);
		}
	}
}

void MapHandler::LoadMap(const std::string& fileName)
{
	//Check if we alreday have a map drawn
	if (map != nullptr)
	{
		
		delete map;
	}
	
	map = new Tmx::Map();

	//Load the map file
	map->ParseFile(fileName);
	mapHeight = map->GetHeight();
	mapWidth = map->GetWidth();
	tileHeight = map->GetTileHeight();
	tileWidth = map->GetTileWidth();

	tileSets = map->GetTilesets();
	tileLayers = map->GetTileLayers();

	
	// Load in all the texture to the specific tile map
	for (size_t i = 0; i < tileSets.size(); i++)
	{
		sf::Texture texture;
		sf::Image image;

		if (!image.loadFromFile(tileSets[i]->GetImage()->GetSource()))
		{
			assert(!"Couldn't load file!");
		}

		//Check if the texture for the tilset have a transparent color
		if (tileSets[i]->GetImage()->HasTransparentColor())
		{
			//Get the transparent color on the texture and create a mask for it
			const Tmx::Color* color = tileSets[i]->GetImage()->GetTransparentColor();
			image.createMaskFromColor(sf::Color(color->GetRed(), color->GetGreen(), color->GetBlue(), 255));
		}
		texture.loadFromImage(image);
		tileTextures.push_back(texture);
	}

	for (auto tiles : tileLayers)
	{
		//Making a vertexarray so it can act as a list of quads
		//vertexLayers.push_back(new sf::VertexArray(sf::Quads, mapHeight * mapWidth * 4));
		vertexLayers.push_back(new MapTexture());

		for (size_t i = 0; i < mapHeight; i++)
		{
			for (size_t j = 0; j < mapWidth; j++)
			{
				//Get the current tile and check if its in the tileset
				const Tmx::MapTile tile = tiles->GetTile(j, i);
				if (tile.tilesetId == -1)
					continue;
				//Get the current layer
				sf::VertexArray* vertexLayer = *(vertexLayers.end() - 1);
				//Get the quad
				sf::Vertex* quad = &(*vertexLayer)[(i * mapWidth + j) * 4];

				//Find the position in the tileset texture
				unsigned int tileNumber = tile.id;
				int tu;
				int tv;
				
				std::cout << tile.tilesetId << std::endl;
				
				tu = tileNumber % (tileTextures[tile.tilesetId].getSize().x / tileWidth);
				tv = tileNumber / (tileTextures[tile.tilesetId].getSize().x / tileWidth);

				/*
				for (size_t k = 0; k < tileTextures.size(); k++)
				{
					//tile.gid >= tileSets[k]->GetFirstGid() + tileSets[k]->GetTiles().size()
					if (tile.gid > tileSets[k]->GetFirstGid() + tileSets[k]->GetTiles().size())
					{
						tu = tileNumber % (tileTextures[k].getSize().x / tileWidth);
						tv = tileNumber / (tileTextures[k].getSize().x / tileWidth);
						break;
					}

					
				}
				*/
				//Define the quads 4 corners
				quad[0].position = sf::Vector2f(j * tileWidth, i * tileHeight);
				quad[1].position = sf::Vector2f((j + 1) * tileWidth, i * tileHeight);
				quad[2].position = sf::Vector2f((j + 1) * tileWidth, (i + 1) * tileHeight);
				quad[3].position = sf::Vector2f(j * tileWidth, (i + 1) * tileHeight);

				std::array<size_t, 4> texOrder = { 0, 1, 2, 3 };

				if (tile.flippedHorizontally)
					texOrder = { 1,0,3,2 };
				//Define its 4 corners in the texture coordinates
				quad[texOrder[0]].texCoords = sf::Vector2f(tu * tileWidth, tv * tileHeight);
				quad[texOrder[1]].texCoords = sf::Vector2f((tu + 1) * tileWidth, tv * tileHeight);
				quad[texOrder[2]].texCoords = sf::Vector2f((tu + 1) * tileWidth, (tv + 1) * tileHeight);
				quad[texOrder[3]].texCoords = sf::Vector2f(tu * tileWidth, (tv + 1) * tileHeight);

			}
		}
	}

}

void ce::MapHandler::DrawMap(sf::RenderWindow& window)
{
	/*
	for (size_t i = 0; i < tileTextures.size(); i++)
	{
		sf::RenderStates* state = new sf::RenderStates;
		state->texture = &tileTextures[i];
		states.push_back(state);
	}
	*/

	for (auto i : vertexLayers)
	{
		/*for (auto j : states)
		{
			window.draw(*i, *j);
		}*/
		sf::RenderStates s;
		s.texture = *i->GetTexture();
		window.draw(*i->GetVertexArray(), s);
	}

	/*
	for (auto it = states.begin(); it != states.end();)
	{
		delete (*it);

		it = states.erase(it);
	}
	*/
}

void ce::MapHandler::AddMapName(std::string* mapName)
{
	tileMapNames.push_back(mapName);
}

void ce::MapHandler::AddMapNameIndex(int & index, std::string* mapName)
{
	tileMapNames.insert(tileMapNames.begin() + index, mapName);
}

void ce::MapHandler::DoBind(lua_State * L)
{
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Chef")
			.beginClass<MapHandler>("MapHandler")
				.addConstructor<void(*)(void)>()
				.addFunction("LoadMap", &MapHandler::LoadMap)
				.addFunction("LoadMapIndex", &MapHandler::LoadMap)
				.addFunction("AddMapName", &MapHandler::AddMapName)
				.addFunction("AddMapNameIndex", &MapHandler::AddMapNameIndex)
			.endClass()
		.endNamespace();
}


