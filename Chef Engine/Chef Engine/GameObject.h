#pragma once
#include "Object.h"
#include <vector>
#include <string>
#include <typeinfo>

namespace ce
{
	class Component;

	class GameObject : public ce::Object
	{
	public:
		GameObject();
		GameObject(std::string name);

		template<typename T>
		T* AddComponent();

		template<typename T>
		T* GetComponent();

		template<typename T>
		void RemoveComponent(T);

		void SetActive(bool active);

		enum Layers { Default, Player, Enemy, Terrain, UI };
		
		Layers layer = Default;

		unsigned long long instanceID;

		bool isNew;

		unsigned long long uniqueIDCounter;

		bool operator==(const GameObject& other);

	private:
		
		friend class GameObjectManager;

		// All the components the GameObject is currently holding
		std::vector<Component*> components;

		void ComponentUpdate();

		bool m_active = true;
	};


	template<typename T>
	T* GameObject::AddComponent()
	{
		T* t = new T();

		components.push_back(t);

		return t;
	}


	template<typename T>
	T* GameObject::GetComponent()
	{
		for (auto it = components.begin(); it != components.end(); it++)
		{
			if (typeid(dynamic_cast<T*>((*it))).hash_code() == typeid(T*).hash_code())
			{
				return (T*)(*it);
			}
		}

		return nullptr;
	}


	template<typename T>
	void GameObject::RemoveComponent(T)
	{

	}

}
