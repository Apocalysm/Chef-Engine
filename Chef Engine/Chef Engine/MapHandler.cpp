#pragma once

#include "MapHandler.h"

using ce::MapHandler;

MapHandler::MapHandler()
{
}


MapHandler::~MapHandler()
{
}

void ce::MapHandler::LoadMap(const int mapIndex)
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
	if (map != nullptr)
	{
		delete map;
	}
	
	map = new Tmx::Map();

	map->ParseFile(fileName);
	mapHeight = map->GetHeight();
	mapWidth = map->GetWidth();
	tileHeight = map->GetTileHeight();
	tileWidth = map->GetTileWidth();

	tileSets = map->GetTilesets();
	tileLayers = map->GetTileLayers();

	

	for (size_t i = 0; i < tileSets.size(); i++)
	{
		sf::Texture texture;
		if (!texture.loadFromFile(tileSets[i]->GetImage()->GetSource()))
		{
			assert(!"Couldn't load file!");
		}

		tileTextures.push_back(texture);
	}

	for (auto tiles : tileLayers)
	{
		vertexLayers.push_back(new sf::VertexArray(sf::Quads, mapHeight * mapWidth * 4));

		for (size_t i = 0; i < mapHeight; i++)
		{
			for (size_t j = 0; j < mapWidth; j++)
			{
				const Tmx::MapTile tile = tiles->GetTile(j, i);
				if (tile.tilesetId == -1)
					continue;
				
				sf::VertexArray* vertexLayer = *(vertexLayers.end() - 1);

				sf::Vertex* quad = &(*vertexLayer)[(i * mapWidth + j) * 4];

				unsigned int tileNumber = tile.id;
				int tu = tileNumber % (tileTextures[0].getSize().x / tileWidth);
				int tv = tileNumber / (tileTextures[0].getSize().x / tileWidth);


				quad[0].position = sf::Vector2f(j * tileWidth, i * tileHeight);
				quad[1].position = sf::Vector2f((j + 1) * tileWidth, i * tileHeight);
				quad[2].position = sf::Vector2f((j + 1) * tileWidth, (i + 1) * tileHeight);
				quad[3].position = sf::Vector2f(j * tileWidth, (i + 1) * tileHeight);

				std::array<size_t, 4> texOrder = { 0, 1, 2, 3 };

				if (tile.flippedHorizontally)
					texOrder = { 1,0,3,2 };

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
	for (size_t i = 0; i < tileTextures.size(); i++)
	{
		sf::RenderStates* state = new sf::RenderStates;
		state->texture = &tileTextures[i];
		states.push_back(state);
	}

	for (auto i : vertexLayers)
	{
		for (auto j : states)
		{
			window.draw(*i, *j);
		}
	}
}

void ce::MapHandler::AddMapName(std::string* mapName)
{
	tileMapNames.push_back(mapName);
}

void ce::MapHandler::AddMapName(int & index, std::string* mapName)
{
	tileMapNames.insert(tileMapNames.begin() + index, mapName);
}


