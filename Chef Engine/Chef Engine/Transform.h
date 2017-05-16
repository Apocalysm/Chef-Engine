#pragma once
#include "Component.h"

namespace ce
{
	class Transform : public ce::Component
	{
	public:
		Transform();
		Transform(const sf::Vector2f& position, const float rotation, const sf::Vector2f& scale);
		~Transform();		

		void Start();

		void Update();

        #pragma region Position Methods
		void SetPosition(const sf::Vector2f& newPosition);
		void SetPosition(const float x, const float y);
		
		const sf::Vector2f& GetPosition() const;

        void Move(sf::Vector2f movement);

		const sf::Vector2f GetLastPos() const;

		const sf::Vector2f GetVelocity() const;

		void ResetVelocity();
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
		
		sf::Vector2f position;
		sf::Vector2f lastPos;
		sf::Vector2f velocity;
        float rotation;
		sf::Vector2f scale;
	};
}

