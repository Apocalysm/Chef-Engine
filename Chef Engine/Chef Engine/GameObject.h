#pragma once
#include "Object.h"
#include <vector>
#include <string>
#include <typeinfo>

namespace ce
{
	// Forward declaration
	class Component;
	
	class GameObject : public ce::Object
	{
	public:
		GameObject();
		GameObject(std::string name);

		// Adds a new component to the GameObject based on the typename in the method call
		template<typename T>
		T* AddComponent();

		// Tries to find the component of the specified typename
		template<typename T>
		T* GetComponent();

		// Removes the component of the specified typename if the GameObject is holding one
		template<typename T>
		void RemoveComponent();

		// An enumerator for differentiating our GameObjects between layers
		enum Layers { Default, Player, Enemy, Terrain, UI };

		// Overloads the == operator to a method
		bool operator==(const GameObject& other);

		// Getter and setter for m_active variable
		void SetActive(bool active);
		bool GetActive();

		// Getter and setter for layer variable
		void SetLayer(Layers newLayer);
		int GetLayer();

		// Getter for instanceID
		unsigned long long GetID();

	private:
		// Lets GameObjectManager access the private members in GameObjects
		friend class GameObjectManager;

		// All the components the GameObject is currently holding
		std::vector<Component*> components;

		// Updates all the components that our GameObject holds
		void ComponentUpdate();

		// If the gameObject should be considered active or not
		bool m_active = true;

		Layers layer = Default;

		// number to differentiate our different GameObject
		unsigned long long instanceID;

		// We set instanceID with this value 
		static unsigned long long uniqueIDCounter;

		// If we created the object this frame
		bool isNew;
	};

	// Adds a new component of the specified type
	template<typename T>
	T* GameObject::AddComponent()
	{
		// Makes sure that this method only takes types derived from ce::Component
		static_assert((std::is_base_of<ce::Component, T>::value), "Type <T> of GameObject.AddComponent<>() must be of type ce::Component");

		// First checks if we don't already have a component of this type on the GameObject
		if (GameObject::GetComponent<T>() == nullptr)
		{
			// Creates a instance of our type T
			T* t = new T();

			components.push_back(t);

			// Sets the int 'hash' of component to be equal to the types hash_code
			components.back()->hash = typeid(dynamic_cast<T*>(components.back())).hash_code();

			return t;
		}
	}

	// Tries to get a component of the specified type from GameObject's vector 'components'
	template<typename T>
	T* GameObject::GetComponent()
	{
		// Makes sure that this method only takes types derived from ce::Component
		static_assert((std::is_base_of<ce::Component, T>::value), "Type <T> of GameObject.GetComponent<>() must be of type ce::Component");

		// Iterates all of GameObject's components
		for (auto it = components.begin(); it != components.end(); it++)
		{
			// Checks if we find the same hash_code on the two types we are comparing
			if ((*it)->hash == typeid(T*).hash_code())
			{
				// We return the component and casts it to type T
				return (T*)(*it);
			}
		}

		return nullptr;
	}


	template<typename T>
	void GameObject::RemoveComponent()
	{
		// Makes sure that this method only takes types derived from ce::Component
		static_assert((std::is_base_of<ce::Component, T>::value), "Type <T> of GameObject.RemoveComponent<>() must be of type ce::Component");

		// Iterates all of GameObject's components
		for (auto it = components.begin(); it != components.end(); it++)
		{
			// Checks if we find the same hash_code on the two types we are comparing
			if ((*it)->hash == typeid(T*).hash_code())
			{
				// We delete the object from the vector and the memory
				delete (*it);

				it = components.erase(it);
				
				break;
			}
		}
	}
}
