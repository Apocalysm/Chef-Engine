#pragma once
#include "Component.h"

namespace ce
{
	class Transform :
		public ce::Component
	{
	public:
		Transform();
		~Transform();

		void SetRotation(float rotation);
		void SetPosition(const sf::Vector2f& position);
		void SetScale(const sf::Vector2f& scale);
		void Rotate(float angle);

		float rotation;
		sf::Vector2f position;
		sf::Vector2f scale;
	};
}

