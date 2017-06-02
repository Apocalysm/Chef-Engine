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
// Author: Dennis Karlsson
//
////////////////////////////////////////////////////////////


#include "DrawEventManager.h"

#include "DrawableComponent.h"
#include "Component.h"
#include "GameObject.h"
#include "TileMapLayer.h"

#include <SFML\Graphics.hpp>

using ce::DrawEventManager;

// Map with DrawableComponents 
std::map<ce::DrawEventManager::uint64, std::map<ce::DrawEventManager::uint64, ce::DrawableComponent*>> ce::DrawEventManager::enumToMapDrawable;

// Map with DrawableComponents recently created
std::map<ce::DrawEventManager::uint64, std::map<ce::DrawEventManager::uint64, ce::DrawableComponent*>> ce::DrawEventManager::enumToMapNewDrawable;

// Vector containing layers from Tiled to be drawn
std::vector<std::map<int, ce::TileMapLayer*>> ce::DrawEventManager::tileMapLayers;

std::vector<sf::RenderStates> ce::DrawEventManager::renderStates;

ce::DrawEventManager::DrawEventManager()
{
}


void ce::DrawEventManager::AddDrawable(ce::DrawableComponent* drawable)
{
	// Adds the DrawableComponent in the map
	// The key of the outer maps is the drawables draw order and the inner maps key is the drawables objects ID
	enumToMapNewDrawable[drawable->GetDrawOrder()].insert(std::make_pair(drawable->GetGameObject()->GetID(), drawable));
}


void ce::DrawEventManager::RemoveDrawable(DrawableComponent* drawable)
{
	// If there is any drawable
	if (drawable != nullptr)
{
		const unsigned long long ID = drawable->GetGameObject()->GetID();

		// Erases the drawable from the map it belongs to
		if (drawable->GetIsNew())
			enumToMapNewDrawable[drawable->drawOrder].erase(ID);
		else
			enumToMapDrawable[drawable->drawOrder].erase(ID);
	}
}

void ce::DrawEventManager::MoveDrawable(ce::DrawableComponent* drawable, const int newDrawOrder)
{
    // Checks if the drawable is new
    if (!drawable->GetIsNew())
    {
        // Removes the drawable from it's old position
        enumToMapDrawable[drawable->drawOrder].erase(drawable->gameObject->GetID());
        // Adds it to the new position
        enumToMapDrawable[newDrawOrder][drawable->gameObject->GetID()] = drawable;
    }
    else
    {
        // Removes the drawable from it's old position
        enumToMapNewDrawable[drawable->drawOrder].erase(drawable->gameObject->GetID());
        // Adds it to the new position
        enumToMapNewDrawable[newDrawOrder][drawable->gameObject->GetID()] = drawable;
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

	// Adds as many empty DrawableMaps as the size of m_timeMapLayers
	// This ensures that the layers will be drawn in case there are too few draw orders for drawables
	for (auto i = 0; i < tileMapLayers.size(); i++)
	{
		DrawableMap map;
		enumToMapDrawable.insert(std::make_pair(i, map));
	}
}


void ce::DrawEventManager::Draw(sf::RenderWindow& window)
{
	if (!enumToMapDrawable.empty())
	{
		for (auto outer_it = enumToMapDrawable.begin(); outer_it != enumToMapDrawable.end(); outer_it++)
		{
			// Draws the layer that has the same order as the current order to draw
			if (outer_it->first < tileMapLayers.size())
			{
				for (auto layer_it = tileMapLayers[outer_it->first].begin(); layer_it != tileMapLayers[outer_it->first].end(); layer_it++)
				{
					window.draw(layer_it->second->GetVertexArray(), renderStates[layer_it->first]);
				}
			}
			
			// If there is any drawable in the map
			if (!outer_it->second.empty())
			{
				for (auto inner_it = outer_it->second.begin(); inner_it != outer_it->second.end(); inner_it++)
				{
					// Draws the drawable if both the component and its gameObject is enabled and active
					if (inner_it->second->GetEnabled() && inner_it->second->gameObject->GetActive())
						window.draw(*inner_it->second->GetDrawable());
				}
			}
		}
	}

	if (!enumToMapNewDrawable.empty())
	{
		for (auto outer_it = enumToMapNewDrawable.begin(); outer_it != enumToMapNewDrawable.end(); outer_it++)
		{
			// If there is any drawable in the map
			if (!outer_it->second.empty())
			{
				for (auto inner_it = outer_it->second.begin(); inner_it != outer_it->second.end(); inner_it++)
				{
					// Draws the drawable if both the component and its gameObject is enabled and active
					if (inner_it->second->GetEnabled() && inner_it->second->gameObject->GetActive())
						window.draw(*inner_it->second->GetDrawable());

					inner_it->second->SetIsNew(false);

					// Adds the new object to the other map since it isn't new anymore
					enumToMapDrawable[inner_it->second->drawOrder].insert(std::make_pair(inner_it->second->gameObject->GetID(), inner_it->second));
				}

				// Clears all the inner maps since they shouldn't contain anything anymore
				outer_it->second.clear();
			}
		}
	}
}