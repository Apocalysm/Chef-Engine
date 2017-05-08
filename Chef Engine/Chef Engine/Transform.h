#pragma once
#include "Component.h"

namespace ce
{
	class Transform :
		public ce::Component
	{
	public:
		Transform();
		Transform(const sf::Vector2f& position, const float rotation, const sf::Vector2f& scale);
		~Transform();		

		void Start();

		void SetPosition(const sf::Vector2f& newPosition);
		void SetPosition(const float x, const float y);
		
		const sf::Vector2f& GetPosition() const;

		void SetRotation(float newRotation);

		float GetRotation() const;

		void Rotate(float angle);
		
		void SetScale(const sf::Vector2f& newScale);
		void SetScale(const float x, const float y);

		sf::Vector2f GetScale() const;


	private:
		float rotation;
		sf::Vector2f position;
		sf::Vector2f scale;
	};
}

