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
        typedef unsigned long long int64;

		typedef std::map<int64, GameObject*> GameObjectMap;
		typedef std::map<int64, GameObjectMap> LayerObjectMap;

		// Map with GameObjects 
		static LayerObjectMap enumToMapObj;

		// Map with GameObjects recently created
		static LayerObjectMap enumToMapNewObj;
	};
}