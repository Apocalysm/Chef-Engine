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

		// This decides if the Component should be updated for example via the Update method
		bool enabled = true;

		// The GameObject holding this Component
		GameObject* gameObject;

		void Start();
		// This gets called every frame from the GameObjectManager
		void Update();
	};
}

