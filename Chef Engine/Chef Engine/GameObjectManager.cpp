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


#include "GameObjectManager.h"
#include "GameObject.h"

#include <utility>

// Map with GameObjects 
std::map<uint64, std::map<uint64, ce::GameObject*>> ce::GameObjectManager::enumToMapObj;

// Map with GameObjects recently created
std::map<uint64,std::map<uint64, ce::GameObject*>> ce::GameObjectManager::enumToMapNewObj;


ce::GameObjectManager::GameObjectManager()
{
	for (int i = 0; i < ce::GameObject::LAYER_AMOUNT; i++)
	{
		GameObjectMap map;
		enumToMapObj.insert(std::make_pair(i, map));
		enumToMapNewObj.insert(std::make_pair(i, map));
	}
}


void ce::GameObjectManager::AddObject(GameObject* object)
{
	enumToMapNewObj[object->layer].insert(std::make_pair(object->instanceID, object));
}


void ce::GameObjectManager::RemoveObject(GameObject* object)
{
	const unsigned long long ID = object->instanceID;
	int layer = object->layer;

	if (object->isNew)
	{
		// Deletes and erases the requested object from the map of new objects
		//delete enumToMapNewObj[layer][ID];
		enumToMapNewObj[layer].erase(ID);
	}
	else
	{
		// Deletes and erases the requested object from the map of objects
		//delete enumToMapObj[layer][ID];
		enumToMapObj[layer].erase(ID);
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
            // If there is any object in the map
            if (!outer_it->second.empty())
            {
                // Iterates through every object in the map
                for (auto inner_it = outer_it->second.begin(); inner_it != outer_it->second.end(); inner_it++)
                {
                    // Updates the object
                    if (inner_it->second->active)
                    {
                        //Calls Start methods of all the object's components
                        inner_it->second->ComponentStart();
                        //Calls Update methods of all the object's components
                        inner_it->second->ComponentUpdate();
                    }
                }
            }
        }
    }

	// If there are any maps in the map
	if (!enumToMapNewObj.empty())
	{
		// Iterates through every map in the map
		for (auto outer_it = enumToMapNewObj.begin(); outer_it != enumToMapNewObj.end(); outer_it++)
		{
			// If there is any object in the map
			if (!outer_it->second.empty())
			{
				// Iterates through every object in the map
				for (auto inner_it = outer_it->second.begin(); inner_it != outer_it->second.end(); inner_it++)
				{
                    if (inner_it->second->active)
                    {
                        //Calls Start methods of all the object's components
                        inner_it->second->ComponentStart();
                        //Calls Update methods of all the object's components
                        inner_it->second->ComponentUpdate();
                    }
					inner_it->second->isNew = false;

					// Adds the new object to the other map since it isn't new anymore
					enumToMapObj[inner_it->second->layer].insert(std::make_pair(inner_it->second->instanceID, inner_it->second));
				}

				// Clears all the inner maps since they shouldn't contain anything anymore
				outer_it->second.clear();
			}
		}
	}
}
