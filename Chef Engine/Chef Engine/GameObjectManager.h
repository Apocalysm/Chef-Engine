#pragma once
#include <iostream>
#include <map>
#include <vector>

namespace ce
{
	class GameObject;

	class GameObjectManager
	{
	public:
		typedef std::map<int, GameObject*> GameObjectMap;
		typedef std::map<int, GameObjectMap> LayerObjectMap;

		GameObjectManager();

		void AddObject(GameObject* object);
		void RemoveObject(GameObject* object);
		void Update();

	private:
		GameObject* gameObj;

		LayerObjectMap enumToVectorObj;
		LayerObjectMap newObjects;
	};
}