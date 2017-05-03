#include "DrawEventManager.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Component.h"

using ce::DrawEventManager;

// Map with Sprites 
std::map<int, std::map<int, ce::Sprite*>> ce::DrawEventManager::enumToMapSpr;

// Map with Sprites recently created
std::map<int, std::map<int, ce::Sprite*>> ce::DrawEventManager::enumToMapNewSpr;

DrawEventManager::DrawEventManager()
{
	for (int i = 0; i < ce::GameObject::LAYER_AMOUNT; i++)
	{
		SpriteMap map;
		enumToMapSpr.insert(std::make_pair(i, map));
		enumToMapNewSpr.insert(std::make_pair(i, map));
	}
}

void DrawEventManager::AddSprite(ce::Sprite* sprite)
{
	//enumToMapNewSpr[sprite->GetDrawOrder()].insert(std::make_pair(sprite->GetGameObject()->GetID(), sprite));
	enumToMapNewSpr[sprite->GetDrawOrder()].insert(std::make_pair(sprite->GetGameObject()->GetID(), sprite));
}

void ce::DrawEventManager::RemoveSprite(Sprite* sprite)
{
	if (sprite != nullptr)
	{
		const unsigned long long ID = sprite->GetGameObject()->GetID();

		if (sprite->isNew)
			enumToMapNewSpr[sprite->drawOrder].erase(ID);
		else
			enumToMapSpr[sprite->drawOrder].erase(ID);

		delete sprite->sprite;
	}
}

void ce::DrawEventManager::Draw(sf::RenderWindow& window)
{
	if (!enumToMapSpr.empty())
	{
		for (auto outer_it = enumToMapSpr.begin(); outer_it != enumToMapSpr.end(); outer_it++)
		{
			//tilemaps[outer_it->first].draw
			// If there is any sprite in the map
			if (!outer_it->second.empty())
			{
				for (auto inner_it = outer_it->second.begin(); inner_it != outer_it->second.end(); inner_it++)
				{
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


