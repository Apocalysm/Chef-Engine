#pragma once
#include <map>

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

		// Map with GameObjects recently created
		LayerObjectMap enumToMapObj;

		// Map with GameObjects
		LayerObjectMap enumToMapNewObj;
	};
}