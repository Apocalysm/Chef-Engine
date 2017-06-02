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
// Author: Dennis Karlsson
//
////////////////////////////////////////////////////////////


#pragma once

#include "Common.h"
#include "LuaBridgeBinder.h"

namespace sf
{
	class Time;
	class Clock;
}

struct lua_State;

namespace ce
{
	class Timef
	{
		// Befriends the templated Bind function so it can access our protected functions
		friend void LuaBridgeBinder::Bind<ce::Timef>(lua_State*);

	public:
		Timef();
		~Timef();

		static float AsSeconds();

		static unsigned int AsMilliseconds();

		static signed long long AsMicroseconds();

		static float GetDeltaTime();

		CHEF_API static void Update();

	private:
		static sf::Time* time;

		static sf::Time* dt;

		static sf::Clock* dtClock;

		// Binds parts of this script to Lua
		static void DoBind(lua_State* L);
	};
}

