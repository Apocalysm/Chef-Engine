#pragma once
#include "Object.h"

#include <SFML\Graphics.hpp>

class GameObject;

namespace ce
{
	class Component : public ce::Object
	{
	public:
		Component();
		~Component();

		virtual void Start();
		// This gets called every frame from the GameObjectManager
		void Update();

		// Getter for the 'hash'-variable
		int GetHashCode() const;

		// Getter and setter for the 'enabled'-variable
		void SetEnabled(bool enabled);
		bool GetEnabled() const;

		// Getter for 'gameObject'-variable
		//GameObject* GetGameObject() const;

		bool operator==(const Component& other);

	private: 

		// The hash_code of the Component, is set in AddComponent
		int hash;

		// This decides if the Component should be updated for example via the Update method
		bool enabled = true;

		// The GameObject holding this Component
		GameObject* gameObject;

	};
}

