#pragma once
#include "Object.h"
#include "LuaBridgeBinder.h"

#include <SFML\Graphics.hpp>

class GameObject;

namespace ce
{
	class Component : public ce::Object
	{
		// Befriends the templated Bind function so it can access our protected functions
		friend void LuaBridgeBinder::Bind<ce::Component>(lua_State*);

	public:
		Component();
		~Component();

		virtual void Start();
		// This gets called every frame from the GameObjectManager
		void Update();

		// Getter for the 'hash'-variable
		int GetHashCode() const;
		void SetHashCode(int hash);

		// Getter and setter for the 'enabled'-variable
		void SetEnabled(bool enabled);
		bool GetEnabled() const;

		// Getter for 'gameObject'-variable
		GameObject* GetGameObject() const;

		bool operator==(const Component& other);

	protected: 
		// Binds all relevant members of this class with LuaBridge
		static void DoBind(lua_State* L);

	private: 

		// The hash_code of the Component, is set in AddComponent
		int hash;

		// This decides if the Component should be updated for example via the Update method
		bool enabled = true;

		// The GameObject holding this Component
		GameObject* gameObject;

	};
}

