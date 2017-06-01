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

////////////////////////////////////////////////////////////
//
// Author: Oskar Svensson (again, based on Vector2.inl in \include\SFML\System\Vector2.inl provided with SFML)
//
////////////////////////////////////////////////////////////

#pragma once
#include "LuaBridgeBinder.h"
#include <string>

struct lua_State;

namespace sf
{
    template<typename T>
    class Vector2;

    typedef Vector2<float> Vector2f;
    typedef Vector2<int> Vector2i;
    typedef Vector2<unsigned int> Vector2u;
}

struct b2Vec2;

namespace ce
{
    ////////////////////////////////////////////////////////////
    /// \brief Representation of 2D vectors and points
    /// In Lua the class is called with it's full name: Vector2
    /// The available variants of this class are: Vector2f(float), Vector2i(int) and Vector2u(unsigned int).
    /// In the examples of this class, I will only be using the float kind, Vector2f.
    ////////////////////////////////////////////////////////////
    template<typename T>
    class Vec2
    {
        // Befriends the templated Bind function so it can access our protected functions
        friend void LuaBridgeBinder::Bind<ce::Vec2<T>>(lua_State*, const std::string&);

    public:
        // Internal
        Vec2();
        ////////////////////////////////////////////////////////////
        /// \brief Constructor for Vector2
        /// Constructs a new Vector2 with the given x, y values
        /// 
        /// \code
        /// -- Creates a new Vector2f
        /// 
        /// spawnPoint = Chef.Vector2f(50, 60)
        /// \endcode
        ////////////////////////////////////////////////////////////
        Vec2(T _x, T _y);
        Vec2(const Vec2<T>& other);

        // External
        Vec2(const sf::Vector2<T>& other);
        Vec2(const b2Vec2& other);

        const sf::Vector2<T>& ToSfVector2() const;
        const b2Vec2& Tob2Vec2() const;

        T x;
        T y;

    private:
        // Binds parts of this script to Lua
        static void DoBind(lua_State* L, const std::string& s);
    };

    #pragma region Operators
    template <typename T>
    Vec2<T> operator -(const Vec2<T>& right)
    {
        return Vector2<T>(-right.x, -right.y);
    }

    template <typename T>
    Vec2<T>& operator +=(Vec2<T>& left, const Vec2<T>& right)
    {
        left.x += right.x;
        left.y += right.y;

        return left;
    }
    template <typename T>
    Vec2<T>& operator -=(Vec2<T>& left, const Vec2<T>& right)
    {
        left.x -= right.x;
        left.y -= right.y;

        return left;
    }

    template <typename T>
    Vec2<T> operator +(const Vec2<T>& left, const Vec2<T>& right)
    {
        return Vector2<T>(left.x + right.x, left.y + right.y);
    }
    template <typename T>
    Vec2<T> operator -(const Vec2<T>& left, const Vec2<T>& right)
    {
        return Vector2<T>(left.x - right.x, left.y - right.y);
    }
    template <typename T>
    Vec2<T> operator *(const Vec2<T>& left, T right)
    {
        return Vector2<T>(left.x * right, left.y * right);
    }
    template <typename T>
    Vec2<T> operator *(T left, const Vec2<T>& right)
    {
        return Vector2<T>(right.x * left, right.y * left);
    }
    template <typename T>
    Vec2<T>& operator *=(Vec2<T>& left, T right)
    {
        left.x *= right;
        left.y *= right;

        return left;
    }
    template <typename T>
    Vec2<T> operator /(const Vec2<T>& left, T right)
    {
        return Vector2<T>(left.x / right, left.y / right);
    }
    template <typename T>
    Vec2<T>& operator /=(Vec2<T>& left, T right)
    {
        left.x /= right;
        left.y /= right;

        return left;
    }
    template <typename T>
    bool operator ==(const Vec2<T>& left, const Vec2<T>& right)
    {
        return (left.x == right.x) && (left.y == right.y);
    }
    template <typename T>
    bool operator !=(const Vec2<T>& left, const Vec2<T>& right)
    {
        return (left.x != right.x) || (left.y != right.y);
    }
    #pragma endregion

    typedef Vec2<float> Vec2f;
    typedef Vec2<int> Vec2i;
    typedef Vec2<unsigned int> Vec2u;
}