#pragma once
#include "Object.h"
#include <vector>

namespace ce
{
	class Component;

	class GameObject : public ce::Object
	{
	public:
		GameObject(std::string name);
		~GameObject();

		template<typename T>
		T& GetComponent(T);

		template<typename T>
		T AddComponent(T);

		template<typename T>
		void RemoveComponent(T);

	private:
		// All the components the GameObject is currently holding
		std::vector<Component*> components;
	};
}

