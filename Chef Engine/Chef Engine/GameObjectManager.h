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
		GameObjectManager();

		void AddObject(GameObject* object);
		void RemoveObject(GameObject* object);

	private:
		GameObject* gameObj;

		std::map<int, std::vector<GameObject*>> enumToVectorObj;
		std::map<int, std::vector<GameObject*>> newObjects;
	};
}