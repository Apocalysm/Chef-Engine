#include "GameObjectManager.h"
#include "GameObject.h"
#include <utility>

ce::GameObjectManager::GameObjectManager()
{
	/*std::vector<GameObject*> defaultObjects;
	enumToVectorObj[Default] = defaultObjects;*/


}

void ce::GameObjectManager::AddObject(GameObject* object)
{
	//newObjects[object->layer].push_back(object)
	newObjects[object->layer].insert(std::make_pair(object->instanceID, object));
}

void ce::GameObjectManager::RemoveObject(GameObject* object)
{
	int ID = object->instanceID;

	if (object->isNew)
	{
		delete newObjects[object->layer][ID];
		newObjects[object->layer].erase(ID);
	}
	else
	{
		delete enumToVectorObj[object->layer][ID];
		enumToVectorObj[object->layer].erase(ID);
	}
}

void ce::GameObjectManager::Update()
{
	
}
