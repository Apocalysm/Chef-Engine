#pragma once

#include <SFML\Graphics.hpp>
#include "LuaBridgeBinder.h"

namespace ce
{
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
		static bool GetKey(int key);
		static bool GetKeyDown(int key);
		static bool GetKeyUp(int key);
		static void ResetKeyboard();
		
	private:
		static void DoBind(lua_State* Lua);
		// Don't try to print these, like ever
		static char* newKeys;
		static char* keys;
	};
}

