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

		void SetRotation(float newRotation);
		void SetPosition(const sf::Vector2f& newPosition);
		void SetScale(const sf::Vector2f& newScale);
		void Rotate(float angle);

	private:
		float rotation;
		sf::Vector2f position;
		sf::Vector2f scale;
	};
}

