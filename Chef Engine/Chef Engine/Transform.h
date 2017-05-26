#pragma once
#include "Component.h"
#include "LuaBridgeBinder.h"

namespace ce
{
    ////////////////////////////////////////////////////////////
    /// \brief Component that holds the position, rotation and scale of the object
    /// Transform is added by default to to GameObject's so you can't add or remove it specifically
    /// Accessing the Transform of an object is done via GameObject.transform
    ///
    /// \code
    /// -- Sets the position, rotation and scale of the GameObject "object"'s Transform component
    ///
    /// object.transform.position = Chef.Vector2f(100, 100)
    /// object.transform.rotation = 90
    /// object.transform.scale = Chef.Vector2f(3, 4)
    /// \endcode
    ////////////////////////////////////////////////////////////
	class Transform : public ce::Component
	{
        // Befriends the templated Bind function so it can access our protected functions
        friend void LuaBridgeBinder::Bind<ce::Transform>(lua_State*);

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

        ////////////////////////////////////////////////////////////
        /// \brief Moves the object by a specified amount of units
        /// \code
        /// -- Moves the GameObject "object" 50 units on the x-axis
        ///
        /// object.transform:Move(Chef.Vector2f(50, 0))
        /// \endcode
        ////////////////////////////////////////////////////////////
        void Move(sf::Vector2f movement);

        #pragma endregion

        #pragma region Rotation Methods
		void SetRotation(float newRotation);

		float GetRotation() const;


        ////////////////////////////////////////////////////////////
        /// \brief Rotates the object with a specified angle
        /// \code
        /// -- Angles the GameObject "object" by 50 degrees
        ///
        /// object.transform:Rotate(50)
        /// \endcode
        ////////////////////////////////////////////////////////////
		void Rotate(float angle);
        #pragma endregion

        #pragma region Scale Methods
		void SetScale(const sf::Vector2f& newScale);
		void SetScale(const float x, const float y);

		sf::Vector2f GetScale() const;
        #pragma endregion

		void SetGameObject(GameObject* gameObject);

	private:
        ////////////////////////////////////////////////////////////
        /// \brief The world position of the object holding the Transform component
        ///
        /// Is set by using Chef.Vector2f
        ///
        /// \code
        /// -- Sets the position of the GameObject "object"
        ///
        /// object.transform.position = Chef.Vector2f(100, 50)
        /// \endcode
        ////////////////////////////////////////////////////////////
		sf::Vector2f position;

        ////////////////////////////////////////////////////////////
        /// \brief The world rotation of the object holding the Transform component
        ///
        /// Is set with a float using degrees
        ///
        /// \code
        /// -- Sets the rotation of the GameObject "object"
        ///
        /// object.transform.rotation = 180
        /// \endcode
        ////////////////////////////////////////////////////////////
        float rotation;

        ////////////////////////////////////////////////////////////
        /// \brief The world scale of the object holding the Transform component
        ///
        /// Is set by using Chef.Vector2f
        ///
        /// \code
        /// -- Sets the scale of the GameObject object
        ///
        /// object.transform.scale = Chef.Vector2f(3, 5)
        /// \endcode
        ////////////////////////////////////////////////////////////
		sf::Vector2f scale;

        // Binds parts of this script to Lua
        static void DoBind(lua_State* L);
	};
}

