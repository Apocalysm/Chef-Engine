#include "DrawEventManager.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Component.h"

using ce::DrawEventManager;

// Map with Sprites 
std::map<int, std::map<int, ce::Sprite*>> ce::DrawEventManager::enumToMapSpr;

// Map with Sprites recently created
std::map<int, std::map<int, ce::Sprite*>> ce::DrawEventManager::enumToMapNewSpr;

// Vector containing layers from Tiled to be drawn
std::vector<sf::VertexArray> ce::DrawEventManager::m_tileMapLayers;

sf::RenderStates ce::DrawEventManager::renderState;


DrawEventManager::DrawEventManager()
{
}

void DrawEventManager::AddSprite(ce::Sprite* sprite)
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

		// Deletes the components sprite
		delete sprite->sprite;
	}
}

void ce::DrawEventManager::AddTmxLayers(std::vector<sf::VertexArray>* tileMapLayers, sf::RenderStates state)
{
	m_tileMapLayers = *tileMapLayers;
	renderState = state;

	// Adds as many empty SpriteMaps as the size of m_timeMapLayers
	// This ensures that the layers will be drawn in case there are too few draw orders for sprites
	for (int i = 0; i < m_tileMapLayers.size(); i++)
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
			if (outer_it->first < m_tileMapLayers.size())
				window.draw(m_tileMapLayers[outer_it->first], renderState);
			
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