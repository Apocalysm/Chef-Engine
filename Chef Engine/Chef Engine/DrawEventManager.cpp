#include "DrawEventManager.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Component.h"

using ce::DrawEventManager;

DrawEventManager::DrawEventManager()
{

}

void DrawEventManager::AddSprite(ce::Sprite* sprite)
{
	enumToMapNewSpr[sprite->GetDrawOrder()].insert(std::make_pair(sprite->GetGameObject()->GetID(), sprite));
}

void ce::DrawEventManager::RemoveSprite(Sprite * sprite)
{
	const unsigned long long ID = sprite->GetGameObject()->GetID();

	if (sprite->isNew)
	{
		// Deletes and erases the requested sprite from the map of new sprites
		delete enumToMapNewSpr[sprite->drawOrder][ID];
		enumToMapNewSpr[sprite->drawOrder].erase(ID);
	}
	else
	{
		// Deletes and erases the requested sprite from the map of sprites
		delete enumToMapSpr[sprite->drawOrder][ID];
		enumToMapSpr[sprite->drawOrder].erase(ID);
	}
}

void ce::DrawEventManager::Draw(sf::RenderWindow& window)
{
	if (!enumToMapSpr.empty())
	{
		for (auto outer_it = enumToMapSpr.begin(); outer_it != enumToMapSpr.end(); outer_it++)
		{
			for (auto inner_it = outer_it->second.begin(); inner_it != outer_it->second.end(); inner_it++)
			{
				if (inner_it->second->GetEnabled() && inner_it->second->gameObject->GetActive())
					window.draw(*inner_it->second->sprite);
			}
		}
	}

	if (!enumToMapNewSpr.empty())
	{
		for (auto outer_it = enumToMapNewSpr.begin(); outer_it != enumToMapNewSpr.end(); outer_it++)
		{
			for (auto inner_it = outer_it->second.begin(); inner_it != outer_it->second.end(); inner_it++)
			{
				if (inner_it->second->GetEnabled() && inner_it->second->gameObject->GetActive())
					window.draw(*inner_it->second->sprite);

				inner_it->second->isNew = false;

				// Adds the new object to the other map since it isn't new anymore
				enumToMapSpr[inner_it->second->drawOrder].insert(std::make_pair(inner_it->second->gameObject->GetID(), inner_it->second));

				// Removes the object from the map of new objects
				enumToMapNewSpr[inner_it->second->drawOrder].erase(inner_it->second->gameObject->GetID());
			}
		}
	}
}


