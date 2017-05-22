#pragma once
#include "Component.h"
#include "LuaBridgeBinder.h"

namespace ce
{
	class Transform : public ce::Component
	{
        // Befriends the templated Bind function so it can access our protected functions
        friend void LuaBridgeBinder::Bind<ce::Transform>(lua_State*);

	public:
		Transform();
		Transform(const sf::Vector2f& position, const float rotation, const sf::Vector2f& scale);
		~Transform();		

		void Start();

        #pragma region Position Methods
		void SetPosition(const sf::Vector2f& newPosition);
		void SetPosition(const float x, const float y);
		
		const sf::Vector2f& GetPosition() const;

        void Move(sf::Vector2f movement);
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
        float rotation;
		sf::Vector2f scale;

        // Binds parts of this script to Lua
        static void DoBind(lua_State* L);
	};
}

