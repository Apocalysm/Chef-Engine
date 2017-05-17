#include "MapHandler.h"
#include "DrawEventManager.h"
#include "Sprite.h"

#include <Tmx\TmxPolygon.h>
#include <Tmx\TmxPolyline.h>
#include <Tmx\TmxEllipse.h>


#include <algorithm>
#include <iostream>

using ce::MapHandler;


MapHandler::MapHandler()
{
}


MapHandler::~MapHandler()
{
}


//Load map with an index number
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

const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
const unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
const unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;

//Load map with its file name
void MapHandler::LoadMap(const std::string& fileName)
{
	//Check if we alreday have a map drawn
	if (map != nullptr)
	{	
		delete map;

		for (auto outer_it = tileMapLayers.begin(); outer_it != tileMapLayers.end(); outer_it++)
		{
			for (auto inner_it = outer_it->begin(); inner_it != outer_it->end();inner_it++)
			{
				delete inner_it->second;
			}
			outer_it->clear();
		}
		for (auto i = gameObjects.begin(); i != gameObjects.end(); i++)
		{
			(*i)->Destroy();
		}

		tileMapLayers.clear();
		tileTextures.clear();
		gameObjects.clear();
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

	for (auto k = 0; k < tileLayers.size(); k++)
	{
		tileMapLayers.push_back(std::map<int, ce::TileMapLayer*>());

		for (size_t i = 0; i < mapHeight; i++)
		{
			for (size_t j = 0; j < mapWidth; j++)
			{
				//Get the current tile and check if its in the tileset
				const Tmx::MapTile tile = tileLayers[k]->GetTile(j, i);
				if (tile.tilesetId == -1)
					continue;


				if (tileMapLayers[k].find(tile.tilesetId) == tileMapLayers[k].end())
				{
					tileMapLayers[k].insert(std::make_pair(tile.tilesetId, 
						new TileMapLayer(new sf::VertexArray(sf::Quads, mapHeight * mapWidth * 4), tileTextures[tile.tilesetId])));
				}
				
				//Get the current layer
				sf::VertexArray& vertexLayer = tileMapLayers[k][tile.tilesetId]->GetVertexArray();
				//Get the quad
				sf::Vertex* quad = &vertexLayer[(i * mapWidth + j) * 4];

				

				//Find the position in the tileset texture
				unsigned int tileNumber = tile.id;
				int tu;
				int tv;
								
				tu = tileNumber % (tileTextures[tile.tilesetId].getSize().x / tileWidth);
				tv = tileNumber / (tileTextures[tile.tilesetId].getSize().x / tileWidth);

				//Define the quads 4 corners
				quad[0].position = sf::Vector2f(j * tileWidth, i * tileHeight);
				quad[1].position = sf::Vector2f((j + 1) * tileWidth, i * tileHeight);
				quad[2].position = sf::Vector2f((j + 1) * tileWidth, (i + 1) * tileHeight);
				quad[3].position = sf::Vector2f(j * tileWidth, (i + 1) * tileHeight);

				std::array<size_t, 4> texOrder = { 0, 1, 2, 3 };

				if (tile.flippedDiagonally)
					texOrder = { 2,3,0,1 };
				else if (tile.flippedHorizontally)
					texOrder = { 1,0,3,2 };
				else if (tile.flippedVertically)
					texOrder = { 3,2,1,0 };
				//Define its 4 corners in the texture coordinates
				quad[texOrder[0]].texCoords = sf::Vector2f(tu * tileWidth, tv * tileHeight);
				quad[texOrder[1]].texCoords = sf::Vector2f((tu + 1) * tileWidth, tv * tileHeight);
				quad[texOrder[2]].texCoords = sf::Vector2f((tu + 1) * tileWidth, (tv + 1) * tileHeight);
				quad[texOrder[3]].texCoords = sf::Vector2f(tu * tileWidth, (tv + 1) * tileHeight);

			}
		}
	}

	std::vector<Tmx::ObjectGroup*> layers = map->GetObjectGroups();;

	//Looping through all the object layers  
	for (auto i = 0; i < layers.size(); i++)
	{
		auto objectsVector = layers[i]->GetObjects();

		std::sort(objectsVector.begin(), objectsVector.end(), [](Tmx::Object* a, Tmx::Object* b) { return a->GetY() < b->GetY(); });

		for (size_t j = 0; j < objectsVector.size(); j++)
		{
			const Tmx::Object* object = objectsVector.at(j);

			ce::GameObject* gameObject = new ce::GameObject(object->GetName());

			gameObjects.push_back(gameObject);

			//Check what type the object is
			switch (object->GetPrimitiveType())
			{
			case Tmx::TMX_PT_POLYGON:
			{

				break;
			}
			case Tmx::TMX_PT_POLYLINE:
			{
				break;
			}

			case Tmx::TMX_PT_ELLIPSE:
			{
				break;
			}

			//Check if the object is an rect or a sprite object
			case Tmx::TMX_PT_NONE:
			{
				//Check if the object is part of an tileset
				if (object->GetGid() != 0)
				{
					ce::Sprite* spriteComponent = gameObject->AddComponent<ce::Sprite>();

					spriteComponent->SetDrawOrder(layers[i]->GetParseOrder());

					spriteComponent->SetRotation(object->GetRot());

					spriteComponent->SetPosition(object->GetX(), object->GetY());


					for (int k = tileSets.size() - 1; k >= 0; k--)
					{
						Tmx::Tileset* ts = tileSets[k];

						bool flipped_horizontally = (object->GetGid() & FLIPPED_HORIZONTALLY_FLAG);
						bool flipped_vertically = (object->GetGid() & FLIPPED_VERTICALLY_FLAG);
						bool flipped_diagonally = (object->GetGid() & FLIPPED_DIAGONALLY_FLAG);

						int unflippedGid = object->GetGid() & ~(FLIPPED_VERTICALLY_FLAG | FLIPPED_HORIZONTALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);

						if (ts->GetFirstGid() <= unflippedGid)
						{
							int localID = unflippedGid - ts->GetFirstGid();


							int tu = localID % (tileTextures[k].getSize().x / tileWidth);
							int tv = localID / (tileTextures[k].getSize().x / tileWidth);

							sf::Sprite* sprite = new sf::Sprite;
							sprite->setTexture(tileTextures[k]);
							sprite->setTextureRect(sf::IntRect(tu * object->GetWidth(), tv * object->GetHeight(), object->GetWidth(), object->GetHeight()));

							if (flipped_diagonally)
								sprite->setTextureRect(sf::IntRect(tu * (object->GetWidth() + 1) - 1, tv * (object->GetHeight() + 1) + 5, -object->GetWidth(), -object->GetHeight()));
							else if (flipped_vertically)
								sprite->setTextureRect(sf::IntRect(tu * object->GetWidth(), tv * (object->GetHeight() + 1) + 5, object->GetWidth(), -object->GetHeight()));
							else if (flipped_horizontally)
								sprite->setTextureRect(sf::IntRect(tu * (object->GetWidth() + 1) - 1, tv * object->GetHeight(), -object->GetWidth(), object->GetHeight()));

							sprite->setOrigin(0, tileHeight);
							spriteComponent->SetRealSprite(sprite);

							break;
						}
					}

				}
				else
				{
					// This is a rect!
					/*sf::RectangleShape* rectShape = new sf::RectangleShape;
					rectShape->setSize(sf::Vector2f(object->GetWidth(), object->GetHeight()));
					rectShape->setPosition(sf::Vector2f(object->GetX(), object->GetY()));
					rectShape->setRotation(object->GetRot());*/
					
					break;
				}

			}


			default:
				break;
			}

		}
	}

	ce::DrawEventManager::AddTmxLayers(tileMapLayers);
}


//Adding the name of a map and where in the vector it should be.
void ce::MapHandler::RegisterMap(int  index, std::string* mapName)
{
	tileMapNames.insert(tileMapNames.begin() + index, mapName);
}


//Loading in all the obect in the map and chech what sort of an object it is. 
void ce::MapHandler::LoadObject()
{
}


void ce::MapHandler::DoBind(lua_State * L)
{
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Chef")
			.beginClass<MapHandler>("MapHandler")
				.addConstructor<void(*)(void)>()
				.addFunction("LoadMap", &MapHandler::LoadMap)
				.addFunction("LoadMapIndex", &MapHandler::LoadMap)
				.addFunction("RegisterMap", &MapHandler::RegisterMap)
			.endClass()
		.endNamespace();
}


