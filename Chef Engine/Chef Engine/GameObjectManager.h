#pragma once
#include <map>
#include <vector>

namespace ce
{
	class GameObject;	// Forward declaration

	class GameObjectManager
	{
	public:
		GameObjectManager();

		void AddObject(GameObject* object);
		void RemoveObject(GameObject* object);
		void CallUpdate();

	private:
		typedef std::map<int, GameObject*> GameObjectMap;
		typedef std::map<int, GameObjectMap> LayerObjectMap;

		LayerObjectMap enumToMapObj;	// Map with GameObjects recently created
		LayerObjectMap enumToMapNewObj;	// Map with GameObjects
	};
}