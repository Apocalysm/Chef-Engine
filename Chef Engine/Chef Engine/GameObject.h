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

		void SetActive(bool active);

		enum Layers { Default, Player, Enemy, Terrain, UI };
		
		Layers layer = Default;

		unsigned long long instanceID;

		bool isNew;
		
		static unsigned long long uniqueIDCounter;

		bool operator==(const GameObject& other);

	private:
		
		friend class GameObjectManager;

		// All the components the GameObject is currently holding
		std::vector<Component*> components;

		void ComponentUpdate();

		bool m_active = true;
	};
}