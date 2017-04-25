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
		map = new Tmx::Map();
	}

	map->ParseFile(fileName);
	mapHeight = map->GetHeight();
	mapWidth = map->GetWidth();
	tileHeight = map->GetTileHeight();
	tileHeight = map->GetTileWidth();

	tmxTileSet = *map->GetTilesets().begin();
	tileLayers = map->GetTileLayers();

	if (!tileSetTexture.loadFromFile(tmxTileSet->GetImage()->GetSource()))
	{
		assert(!"Couldnt load file!");
	}	
}

void ce::MapHandler::DrawMap(sf::RenderWindow window)
{
	sf::RenderStates state;
	state.texture = &tileSetTexture;

	for (auto i : vertexLayers)
	{
		window.draw(*i, state);
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
