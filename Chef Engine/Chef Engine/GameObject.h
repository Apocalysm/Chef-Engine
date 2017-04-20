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

	};
}

