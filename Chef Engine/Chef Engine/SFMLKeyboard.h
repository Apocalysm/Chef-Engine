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
#include "Common.h"
#include "LuaBridgeBinder.h"

struct lua_State;

namespace ce
{
    class LuaBridgeBinder;

    ////////////////////////////////////////////////////////////
    /// \brief Use this class to check for keyboard input in Lua.
    /// 
    /// In Lua you access this class' functions with Chef.Input
    ////////////////////////////////////////////////////////////
	class SFMLKeyboard
	{

		friend void LuaBridgeBinder::Bind<ce::SFMLKeyboard>(lua_State*);

	public:
		CHEF_API SFMLKeyboard();
		CHEF_API ~SFMLKeyboard();

		CHEF_API static void Initialize();
		CHEF_API static void ClearKeys();
		CHEF_API static void SetKeyDown(int key);
		CHEF_API static void SetKeyUp(int key);

        ////////////////////////////////////////////////////////////
        /// \brief Returns true every frame you're pressing the specified key
        /// 
        /// In Lua you access this class' functions with Chef.Input.GetKey()
        ///
        /// \param This is the keyboard key you want to read and you get that key
        /// by writing "Chef.<key>" instead of an int. \n Here is a list of all available keys: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Keyboard-members.php
        ///
        /// \code
        /// -- Checks if we're holding down the 'D' key
        ///
        /// if Chef.Input:GetKey(Chef.D) then
        ///     -- In that case we move the GameObject "object" to the right
        ///     self.object.transform:move(Chef.Vector2(moveSpeed, 0))
        /// end
        /// \endcode
        ////////////////////////////////////////////////////////////
        CHEF_API static bool GetKey(int key);

        ////////////////////////////////////////////////////////////
        /// \brief Returns true the first frame you press the specified key
        /// 
        /// In Lua you access this class' functions with Chef.Input:GetKeyDown()
        ///
        /// \param This is the keyboard key you want to read and you get that key
        /// by writing "Chef.<key>" instead of an int. \n Here is a list of all available keys: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Keyboard-members.php
        ///
        /// \code
        /// -- Checks if we pressed the '+' key
        ///
        /// if Chef.Input:GetKeyDown(Chef.Add) then
        ///     -- In that case we add to an int
        ///     self.counter = counter + 1
        /// end
        /// \endcode
        ////////////////////////////////////////////////////////////
        CHEF_API static bool GetKeyDown(int key);

        ////////////////////////////////////////////////////////////
        /// \brief Returns true when you release the specified key
        /// 
        /// In Lua you access this class' functions with Chef.Input.GetKeyUp()
        ///
        /// \param This is the keyboard key you want to read and you get that key
        /// by writing "Chef.<key>" instead of an int. \n Here is a list of all available keys: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Keyboard-members.php
        ///
        /// \code
        /// -- Checks if we released the 'Space' key
        ///
        /// if Chef.Input:GetKeyUp(Chef.space) then
        ///     -- In that case we allow the player to jump again
        ///     self.canJump = true
        /// end
        /// \endcode
        ////////////////////////////////////////////////////////////
        CHEF_API static bool GetKeyUp(int key);

        CHEF_API static void ResetKeyboard();
		
	private:
		static void DoBind(lua_State* Lua);
		// Don't try to print these, like ever
		static char* newKeys;
		static char* keys;
	};
}

