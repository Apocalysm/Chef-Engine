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


#include "SFMLLuaBind.h"
#include "Camera.h"
#include "LuaBind.h"

#include <SFML\Graphics.hpp>

void SetWindowSize(const ce::Vec2u& size)
{
    ce::Camera::window->setSize(size.ToSfVector2());
}

void ce::SFMLLuaBind::DoBind(lua_State* L)
{
    luabridge::getGlobalNamespace(L)
        .beginNamespace("Chef")
            // Binds SFML Color
            .beginClass<sf::Color>("Color")
                .addConstructor<void(*)(sf::Uint8, sf::Uint8, sf::Uint8, sf::Uint8)>()
                .addData("r", &sf::Color::r)
                .addData("g", &sf::Color::g)
                .addData("b", &sf::Color::b)
                .addData("a", &sf::Color::a)
            .endClass()

            // Binds SFML RenderWindow
            .beginNamespace("Window")
                .addFunction("SetSize", &SetWindowSize)
            .endNamespace()
            
        .endNamespace();
}
