#pragma once
#include "LuaBridgeBinder.h"

#include <SFML\Graphics.hpp>

namespace ce
{
	class GameObject;

	class Component
	{
		// Befriends the templated Bind function so it can access our protected functions
		friend void LuaBridgeBinder::Bind<ce::Component>(lua_State*);

	public:
		Component();
		~Component();

		virtual void Start();
		// This gets called every frame from the GameObjectManager
		virtual void Update();

		// Getter for the 'hash'-variable
		int GetID() const;
		void SetID(int hash);

		// Getter and setter for the 'enabled'-variable
		void SetEnabled(bool enabled);
		bool GetEnabled() const;

		// Getter for 'gameObject'-variable
		GameObject* GetGameObject() const;
		virtual void SetGameObject(GameObject* gameObject);

		bool operator==(const Component& other);

	protected:
		// The GameObject holding this Component
		ce::GameObject* gameObject = nullptr;

	private: 
        static int IDCounter;

		// The hash_code of the Component, is set in AddComponent
		int ID;

		// This decides if the Component should be updated for example via the Update method
		bool enabled = true;

		

	};
}

