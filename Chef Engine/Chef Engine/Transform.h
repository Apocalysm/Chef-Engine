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

        #pragma region Position Methods
		void SetPosition(const sf::Vector2f& newPosition);
		void SetPosition(const float x, const float y);
		
		const sf::Vector2f& GetPosition() const;
        #pragma endregion

        #pragma region Rotation Methods
		void SetRotation(float newRotation);

		float GetRotation() const;

		void Rotate(float angle);
        #pragma endregion

        #pragma region Scale Methods
		void SetScale(const sf::Vector2f& newScale);
		void SetScale(const float x, const float y);

		sf::Vector2f GetScale() const;
        #pragma endregion

	private:
		float rotation;
		sf::Vector2f position;
		sf::Vector2f scale;
	};
}

