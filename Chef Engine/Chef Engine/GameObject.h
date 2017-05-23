#pragma once
#include "LuaComponent.h"
#include "Transform.h"
#include "ContactListener.h"

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <typeinfo>
#include <utility>


namespace ce
{
	// Forward declaration to Component since Component includes GameObject
	class Component;
	
	class GameObject
	{
		// Befriends the templated Bind function so it can access our protected functions
		friend void LuaBridgeBinder::Bind<ce::GameObject>(lua_State*);

        typedef unsigned long long int64;

	public:
		GameObject();
		GameObject(std::string name);

		~GameObject();

        
        #pragma region Component Methods
		// Adds a new component to the GameObject based on the typename in the method call
		template<typename T> 
        T* AddComponent();

		// Tries to find the component of the specified typename
		template<typename T>
		T* GetComponent();

		// Removes the component of the specified typename if the GameObject is holding one
		template<typename T>
		void RemoveComponent(T* component);
        #pragma endregion

        #pragma region LuaComponent Methods
        // Creates and adds a LuaComponent by passing a LuaRef into it
        luabridge::LuaRef AddLuaComponent(luabridge::LuaRef ref);

        luabridge::LuaRef GetLuaComponent(int ID);

        void RemoveLuaComponent(int ID);
      
        #pragma endregion

		enum Layers { Default, Player, Enemy, Terrain, UI};

		// The amount of different values in the Layers enum
		static const int LAYER_AMOUNT;

		// Getter and setter for active variable
		void SetActive(bool active);
		bool GetActive() const;

		// Getter and setter for layer variable
		void SetLayer(Layers newLayer);
		int GetLayer() const;

		void SetTransform(Transform* transform);
		Transform* GetTransform() const;

		// Getter and setter methods for 'name' variable
		std::string GetName() const;
		void SetName(std::string name);

		// Getter and setter methods for 'tag' variable
		std::string GetTag() const;
		void SetTag(std::string tag);

		// Destroys the specified Object instance
		void Destroy();

		// Getter for instanceID
        int64 GetID() const;

		// Overloads the == operator to a method
		bool operator==(const GameObject& other);

    private:
		// Lets GameObjectManager access the private members in GameObjects
		friend class GameObjectManager;
		friend class ContactListener;

		// All the components the GameObject is currently holding
		std::map<int, Component*> components;

        std::map<int, LuaComponent*> luaComponents;

		std::string name;

		// Specifies what kind of Object this is
		std::string tag;

		// If the gameObject should be considered active or not
		bool active;

		Layers layer;

		// number to differentiate our different GameObject
        int64 instanceID;

		// We set instanceID with this value 
		static int64 uniqueIDCounter;

		// If we created the object this frame
		bool isNew;

		Transform* transform;
	    
        // Calls the Start method on all the Components that are marked is new / was created this frame
        void ComponentStart();

        // Updates all the components that our GameObject holds
		void ComponentUpdate();
		
        // Tries to find the component of the specified typename
		template<typename T>
		T* GetComponentInternal();

        // Binds all relevant members of this class with LuaBridge
        static void DoBind(lua_State* L);
	};


	// Adds a new component of the specified type
	template<typename T>
	T* ce::GameObject::AddComponent()
	{
		// Makes sure that this method only takes types derived from ce::Component
		//static_assert((std::is_base_of<ce::Component, T>::value), "Type <T> of GameObject.AddComponent<>() must be of type ce::Component");

        if (!std::is_base_of<ce::Component, T>::value)
            std::cerr << "Type <T> of GameObject.AddComponent<>() must be of type ce::Component" << std::endl;

		// First checks if we don't already have a component of this type on the GameObject
		if (GameObject::GetComponentInternal<T>() == nullptr)
		{
			// Creates a instance of our type T
			T* t = new T();

			t->SetGameObject(this);

			// Sets the int 'ID' of component to be equal to the types ID
			t->SetID(typeid(t).hash_code());
	        
            components.insert(std::make_pair(t->GetID(), t));

			return t;
		}

        return nullptr;
	}

	
	// Tries to get a component of the specified type from GameObject's vector 'components'
	template<typename T>
	T* ce::GameObject::GetComponentInternal()
	{
		// Makes sure that this method only takes types derived from ce::Component
		static_assert((std::is_base_of<ce::Component, T>::value), "Type <T> of GameObject.GetComponent must be of type ce::Component");

		// Iterates all of GameObject's components
		for (auto it = components.begin(); it != components.end(); it++)
		{
			// Checks if we find the same ID on the two types we are comparing
			if ((*it).second->GetID() == typeid(T*).hash_code())
			{
				// We return the component and casts it to type T
				return (T*)(*it).second;
			}
		}

		return nullptr;
	}

	
	// Uses GetComponentInternal and also writes an error message to the console if we couldn't find anything
	template<typename T>
	T* ce::GameObject::GetComponent()
	{
		T* t = GetComponentInternal<T>();

		if (t == nullptr)
		{
			std::cerr << "Could not find component of type <" << typeid(T).name() << ">" << std::endl;
		    return nullptr;
	    }
		return t;
	}


	template<typename T>
	void ce::GameObject::RemoveComponent(T* component)
	{
		// Makes sure that this method only takes types derived from ce::Component
		static_assert((std::is_base_of<ce::Component, T>::value), "Type <T> of GameObject.RemoveComponent<>() must be of type ce::Component");

		// Iterates all of GameObject's components
		for (auto it = components.begin(); it != components.end(); it++)
		{
			// Checks if we find the same ID on the two types we are comparing
			if (it->second->GetID() == component->GetID())
			{
				// We delete the object from the vector and the memory
				delete it->second;

				it = components.erase(it);
				
				break;
			}
		}
	}

}
