////////////////////////////////////////////////////////////
//
// Chef Engine
// Copyright (C) 2017 Oskar Svensson
//  
// This file is based on Vector2.inl in \include\SFML\System\Vector2.inl provided with SFML 
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


#include "Vec2.h"
#include "LuaBind.h"

#include <SFML\System\Vector2.hpp>

// b2Vec2
#include <Box2D\Common\b2Math.h>

using ce::Vec2;

template<typename T>
Vec2<T>::Vec2()
    : x(T())
    , y(T())
{
}


template<typename T>
Vec2<T>::Vec2(T _x, T _y)
    : x(_x)
    , y(_y)
{
}


template<typename T>
Vec2<T>::Vec2(const Vec2<T>& other)
    : x(other.x)
    , y(other.y)
{
}


template<typename T>
Vec2<T>::Vec2(const sf::Vector2<T>& other)
    : x(other.x)
    , y(other.y)
{
}


Vec2<float>::Vec2(const b2Vec2& other)
    : x(other.x)
    , y(other.y)
{
}


template <typename T>
const sf::Vector2<T>& Vec2<T>::ToSfVector2() const
{
    return sf::Vector2<T>(x, y);
}


const b2Vec2& Vec2<float>::Tob2Vec2() const
{
    return b2Vec2(x, y);
}

template <typename T>
void Vec2<T>::DoBind(lua_State* L, const std::string& s)
{
    luabridge::getGlobalNamespace(L)
        .beginNamespace("Chef")
            .beginClass<Vec2<T>>(std::string("Vector2" + s).c_str())
                .addConstructor<void(*)(T, T)>()
                .addData("x", &Vec2<T>::x)
                .addData("y", &Vec2<T>::y)
            .endClass()
        .endNamespace();
}

template class Vec2<float>;
template class Vec2<int>;
template class Vec2<unsigned int>;