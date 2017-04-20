#include "GameObjectManager.h"
#include "GameObject.h"

ce::GameObjectManager::GameObjectManager()
{
	/*std::vector<GameObject*> defaultObjects;
	enumToVectorObj[Default] = defaultObjects;*/
}

void ce::GameObjectManager::AddObject(GameObject* object)
{
	newObjects[object->layer].push_back(object);
	object->
}

void ce::GameObjectManager::RemoveObject(GameObject* object)
{

}
