#pragma once
#include "Object.h"
#include <vector>

namespace ce
{
	class Component;

	class GameObject : public ce::Object
	{
	public:
		GameObject(std::string name);

		template<typename T>
		T& GetComponent(T);

		template<typename T>
		T AddComponent(T);

		template<typename T>
		void RemoveComponent(T);

		enum Layers { Default, Player, Enemy, Terrain, UI };

		Layers layer = Default;

		int instanceID;

		bool isNew;
		
		static unsigned long long uniqueIDCounter;

		bool operator==(const GameObject& other);

		// This is another test
		int newVariable2 = 2982;

	private:
		// All the components the GameObject is currently holding
		std::vector<Component*> components;
	};
}

