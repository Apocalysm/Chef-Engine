#pragma once
#include "Object.h"

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

