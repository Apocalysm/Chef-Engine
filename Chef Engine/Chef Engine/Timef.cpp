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


#include "Timef.h"
#include "LuaBind.h"

#include <SFML\System.hpp>

using ce::Timef;

sf::Time* ce::Timef::time = new sf::Time();
sf::Time* ce::Timef::dt = new sf::Time();
sf::Clock* ce::Timef::dtClock = new sf::Clock();

Timef::Timef()
{
	time = new sf::Time();

	dtClock = new sf::Clock();
}


Timef::~Timef()
{
	delete time;

	delete dtClock;
}


float ce::Timef::AsSeconds()
{
	return time->asSeconds();
}


unsigned int ce::Timef::AsMilliseconds()
{
	return time->asMilliseconds();
}


signed long long ce::Timef::AsMicroseconds()
{
	return time->asMicroseconds();
}


float ce::Timef::GetDeltaTime()
{
	return dt->asSeconds();
}


void ce::Timef::Update()
{
	*dt = dtClock->restart();
}


void ce::Timef::DoBind(lua_State * L)
{
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Chef")
			.beginClass<Timef>("Time")
				.addConstructor<void(*)(void)>()
				.addStaticProperty("seconds", &Timef::AsSeconds)
				.addStaticProperty("milliseconds", &Timef::AsMilliseconds)
				.addStaticFunction("microseconds", &Timef::AsMicroseconds)
				.addStaticProperty("deltaTime", &Timef::GetDeltaTime)
			.endClass()
		.endNamespace();
}
