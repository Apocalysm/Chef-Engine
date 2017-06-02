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

////////////////////////////////////////////////////////////
//
// Author: Rasmus Andersson, Oskar Svensson
//
////////////////////////////////////////////////////////////

#pragma once
#include "LuaBridgeBinder.h"

#include <string>

namespace ce
{
    template <typename T>
    ////////////////////////////////////////////////////////////
    /// \brief Contains common Math functions
    /// Is just called "Math" in Lua.
    /// All functions have a suffix based on what data type you want to use.
    /// For example, all the float functions have the suffix 'f', so the functions
    /// are called "Clampf" and "Lerpf"
    ////////////////////////////////////////////////////////////
	class Mathf
	{
        // Befriends the templated Bind function so it can access our protected functions
        friend void LuaBridgeBinder::Bind<ce::Mathf<T>>(lua_State*);

	public:
        ////////////////////////////////////////////////////////////
        /// \brief Clamps a value
        /// 
        /// \code
        /// -- Clamps position of the player to not go outside a certain point
        /// 
        /// clampedX = Chef.Math.Clampf(self.transform.position.x, maxPosX, minPosX)
        /// clampedY = Chef.Math.Clampf(self.transform.position.y, maxPosY, minPosY)
        /// player.transform.position = Chef.Vector2f(clampedX, clampedY)
        /// 
        /// \endcode
        ////////////////////////////////////////////////////////////
        static T Clamp(T value, T maxValue, T minValue);

        ////////////////////////////////////////////////////////////
        /// \brief Linear interpolation of a value
        /// 
        /// \code
        /// -- Lerps the camera to the player's position 50% every frame
        /// 
        /// lerpX = Chef.Math.Lerpf(self.transform.position.x, enemyPosX, 0.5)
        /// lerpY = Chef.Math.Lerpf(self.transform.position.y, enemyPosY, 0.5)
        /// player.transform.position = Chef.Vector2f(lerpX, lerpY)
        /// 
        /// \endcode
        ////////////////////////////////////////////////////////////
        static T Lerp(T value, T goal, T step);

    private:
        // Binds parts of this script to Lua
        static void DoBind(lua_State* L, const std::string& s);
	};
}
