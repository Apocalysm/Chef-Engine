#pragma once
#include <map>

namespace ce
{
	class GameObject;	// Forward declaration

	class GameObjectManager
	{
	public:
		GameObjectManager();

		static void AddObject(GameObject* object);
		static void RemoveObject(GameObject* object);
		void CallUpdate();

	private:
		typedef std::map<int, GameObject*> GameObjectMap;
		typedef std::map<int, GameObjectMap> LayerObjectMap;

		// Map with GameObjects 
		static LayerObjectMap enumToMapObj;

		// Map with GameObjects recently created
		static LayerObjectMap enumToMapNewObj;
	};
}