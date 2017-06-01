////////////////////////////////////////////////////////////
//
// Chef Engine
// Copyright (C) 2017 
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

#include "DrawEventManager.h"

#include "Component.h"
#include "Sprite.h"
#include "GameObject.h"
#include "TileMapLayer.h"

#include <SFML\Graphics.hpp>

using ce::DrawEventManager;

// Map with Sprites 
std::map<ce::DrawEventManager::uint64, std::map<ce::DrawEventManager::uint64, ce::Sprite*>> ce::DrawEventManager::enumToMapSpr;

// Map with Sprites recently created
std::map<ce::DrawEventManager::uint64, std::map<ce::DrawEventManager::uint64, ce::Sprite*>> ce::DrawEventManager::enumToMapNewSpr;

// Vector containing layers from Tiled to be drawn
std::vector<std::map<int, ce::TileMapLayer*>> ce::DrawEventManager::tileMapLayers;

std::vector<sf::RenderStates> ce::DrawEventManager::renderStates;


ce::DrawEventManager::DrawEventManager()
{
}


void ce::DrawEventManager::AddSprite(ce::Sprite* sprite)
{
	// Adds the sprite component in the map
	// The key of the outer maps is the sprites draw order and the inner maps key is the sprites objects ID
	enumToMapNewSpr[sprite->GetDrawOrder()].insert(std::make_pair(sprite->GetGameObject()->GetID(), sprite));
}


void ce::DrawEventManager::RemoveSprite(Sprite* sprite)
{
	// If there is any sprite
	if (sprite != nullptr)
	{
		const unsigned long long ID = sprite->GetGameObject()->GetID();

		// Erases the sprite from the map it belongs to
		if (sprite->isNew)
			enumToMapNewSpr[sprite->drawOrder].erase(ID);
		else
			enumToMapSpr[sprite->drawOrder].erase(ID);
	}
}

void ce::DrawEventManager::MoveSprite(Sprite* sprite, const int newDrawOrder)
{
    // Checks if the sprite isNew or not
    if (!sprite->isNew)
    {
        // Removes the sprite from it's old position
        enumToMapSpr[sprite->drawOrder].erase(sprite->gameObject->GetID());
        // Adds it to the new position
        enumToMapSpr[newDrawOrder][sprite->gameObject->GetID()] = sprite;
    }
    else
    {
        // Removes the sprite from it's old position
        enumToMapNewSpr[sprite->drawOrder].erase(sprite->gameObject->GetID());
        // Adds it to the new position
        enumToMapNewSpr[newDrawOrder][sprite->gameObject->GetID()] = sprite;
    }

}


void ce::DrawEventManager::AddTmxLayers(std::vector<std::map<int, ce::TileMapLayer*>> layers)
{
	tileMapLayers = layers;

	renderStates.clear();

	for (auto outer_it = tileMapLayers.begin(); outer_it != tileMapLayers.end(); outer_it++)
	{
		for (auto inner_it = outer_it->begin(); inner_it != outer_it->end(); inner_it++)
{
			sf::RenderStates state;
			state.texture = &inner_it->second->GetTexture();
			renderStates.push_back(state);
		}
	}

	// Adds as many empty SpriteMaps as the size of TileMapLayers
	// This ensures that the layers will be drawn in case there are too few draw orders for sprites
	for (auto i = 0; i < tileMapLayers.size(); i++)
	{
		SpriteMap map;
		enumToMapSpr.insert(std::make_pair(i, map));
	}
}


void ce::DrawEventManager::Draw(sf::RenderWindow& window)
{
	if (!enumToMapSpr.empty())
	{
		for (auto outer_it = enumToMapSpr.begin(); outer_it != enumToMapSpr.end(); outer_it++)
		{
			// Draws the layer that has the same order as tha current order to draw
			if (outer_it->first < tileMapLayers.size())
			{
				for (auto layer_it = tileMapLayers[outer_it->first].begin(); layer_it != tileMapLayers[outer_it->first].end(); layer_it++)
				{
					window.draw(layer_it->second->GetVertexArray(), renderStates[layer_it->first]);
				}
			}
			
			// If there is any sprite in the map
			if (!outer_it->second.empty())
			{
				for (auto inner_it = outer_it->second.begin(); inner_it != outer_it->second.end(); inner_it++)
				{
					// Draws the sprite if both the component and its gameObject is enabled and active
					if (inner_it->second->GetEnabled() && inner_it->second->gameObject->GetActive())
						window.draw(*inner_it->second->sprite);
				}
			}
		}
	}

	if (!enumToMapNewSpr.empty())
	{
		for (auto outer_it = enumToMapNewSpr.begin(); outer_it != enumToMapNewSpr.end(); outer_it++)
		{
			// If there is any sprite in the map
			if (!outer_it->second.empty())
			{
				for (auto inner_it = outer_it->second.begin(); inner_it != outer_it->second.end(); inner_it++)
				{
					// Draws the sprite if both the component and its gameObject is enabled and active
					if (inner_it->second->GetEnabled() && inner_it->second->gameObject->GetActive())
						window.draw(*inner_it->second->sprite);

					inner_it->second->isNew = false;

					// Adds the new object to the other map since it isn't new anymore
					enumToMapSpr[inner_it->second->drawOrder].insert(std::make_pair(inner_it->second->gameObject->GetID(), inner_it->second));
				}

				// Clears all the inner maps since they shouldn't contain anything anymore
				outer_it->second.clear();
			}
		}
	}
}