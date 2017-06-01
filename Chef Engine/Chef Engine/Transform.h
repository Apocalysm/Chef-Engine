////////////////////////////////////////////////////////////
//
// Chef Engine
// Copyright (C) 2017 Oskar Svensson
//  
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////


#pragma once
#include "Vec2.h"

#include "Component.h"
#include "LuaBridgeBinder.h"

struct lua_State;

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
		Transform(const Vec2f& position, const float rotation, const Vec2f& scale);
		~Transform();		

		void Start();

		void Update();

        #pragma region Position Methods
		void SetPosition(const Vec2f& newPosition);
		void SetPosition(const float x, const float y);
		
		const Vec2f& GetPosition() const;

        ////////////////////////////////////////////////////////////
        /// \brief Moves the object by a specified amount of units
        /// \code
        /// -- Moves the GameObject "object" 50 units on the x-axis
        ///
        /// object.transform:Move(Chef.Vector2f(50, 0))
        /// \endcode
        ////////////////////////////////////////////////////////////
        void Move(const Vec2f& movement);

        #pragma endregion

        #pragma region Rotation Methods
		void SetRotation(const float newRotation);

		float GetRotation() const;


        ////////////////////////////////////////////////////////////
        /// \brief Rotates the object with a specified angle
        /// \code
        /// -- Angles the GameObject "object" by 50 degrees
        ///
        /// object.transform:Rotate(50)
        /// \endcode
        ////////////////////////////////////////////////////////////
		void Rotate(const float angle);
        #pragma endregion

        #pragma region Scale Methods
		void SetScale(const Vec2f& newScale);
		void SetScale(const float x, const float y);

		const Vec2f& GetScale() const;
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
		Vec2f position;

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
        Vec2f scale;

        // Binds parts of this script to Lua
        static void DoBind(lua_State* L);
	};
}

