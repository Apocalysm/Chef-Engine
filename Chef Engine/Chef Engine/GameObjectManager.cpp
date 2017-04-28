#include "GameObjectManager.h"
#include "GameObject.h"
#include <utility>

// Map with GameObjects 
std::map<int, std::map<int, ce::GameObject*>> ce::GameObjectManager::enumToMapObj;

// Map with GameObjects recently created
std::map<int,std::map<int, ce::GameObject*>> ce::GameObjectManager::enumToMapNewObj;


ce::GameObjectManager::GameObjectManager()
{
	/*std::vector<GameObject*> defaultObjects;
	enumToVectorObj[Default] = defaultObjects;*/
}

void ce::GameObjectManager::AddObject(GameObject* object)
{
	//newObjects[object->layer].push_back(object)
	enumToMapNewObj[object->layer].insert(std::make_pair(object->instanceID, object));
}

void ce::GameObjectManager::RemoveObject(GameObject* object)
{
	const unsigned long long ID = object->instanceID;

	if (object->isNew)
	{
		// Deletes and erases the requested object from the map of new objects
		delete enumToMapNewObj[object->layer][ID];
		enumToMapNewObj[object->layer].erase(ID);
	}
	else
	{
		// Deletes and erases the requested object from the map of objects
		delete enumToMapObj[object->layer][ID];
		enumToMapObj[object->layer].erase(ID);
	}
}

void ce::GameObjectManager::CallUpdate()
{
	// If there is any object in the map
	if (!enumToMapObj.empty())
	{
		// Iterates through every map in the map
		for (auto outer_it = enumToMapObj.begin(); outer_it != enumToMapObj.end(); outer_it++)
		{
			// Iterates through every object in the map
			for (auto inner_it = outer_it->second.begin(); inner_it != outer_it->second.end(); inner_it++)
			{
				// Updates the object
				if (inner_it->second->m_active)
					inner_it->second->ComponentUpdate();
			}
		}
	}

	// If there is any object in the map
	if (!enumToMapNewObj.empty())
	{
		// Iterates through every map in the map
		for (auto outer_it = enumToMapNewObj.begin(); outer_it != enumToMapNewObj.end(); outer_it++)
		{
			// Iterates through every object in the map
			for (auto inner_it = outer_it->second.begin(); inner_it != outer_it->second.end(); inner_it++)
			{
				if(inner_it->second->m_active)
					// Updates the object
					inner_it->second->ComponentUpdate();

				inner_it->second->isNew = false;

				// Adds the new object to the other map since it isn't new anymore
				enumToMapObj[inner_it->second->layer].insert(std::make_pair(inner_it->second->instanceID, inner_it->second));

				// Removes the object from the map of new objects
				enumToMapNewObj[inner_it->second->layer].erase(inner_it->second->instanceID);
			}
		}
	}
}
