#pragma once

#include <SFML\Graphics.hpp>
#include "LuaBridgeBinder.h"

namespace ce
{
    ////////////////////////////////////////////////////////////
    /// \brief Use this class to check for keyboard input in Lua.
    /// 
    /// In Lua you access this class' functions with Chef.Input
    ////////////////////////////////////////////////////////////
	class SFMLKeyboard
	{

		friend void LuaBridgeBinder::Bind<ce::SFMLKeyboard>(lua_State*);

	public:
		SFMLKeyboard();
		~SFMLKeyboard();

		static void Initialize();
		static void ClearKeys();
		static void SetKeyDown(sf::Keyboard::Key key);
		static void SetKeyUp(sf::Keyboard::Key key);

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
		static bool GetKey(int key);

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
		static bool GetKeyDown(int key);

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
		static bool GetKeyUp(int key);

		static void ResetKeyboard();
		
	private:
		static void DoBind(lua_State* Lua);
		// Don't try to print these, like ever
		static char* newKeys;
		static char* keys;
	};
}

