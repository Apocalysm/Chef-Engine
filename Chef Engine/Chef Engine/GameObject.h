#pragma once
#include "Component.h"

namespace ce
{
	class GameObject
	{
	public:
		GameObject(std::string name);
		~GameObject();

		Component GetComponent();

		int layer = Default;

	private:
		enum Layers { Default, Player, Enemy, Terrain, UI };

	};
}

