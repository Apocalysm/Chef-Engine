#pragma once
#include "Object.h"
#include <SFML\Graphics.hpp>

namespace ce
{
	class Component : public ce::Object
	{
	public:
		Component();
		~Component();

		bool enabled = true;


		void Start();

		void Update();
	};
}

