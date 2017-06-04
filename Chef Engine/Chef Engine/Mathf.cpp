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
// Author: Rasmus Andersson
//
////////////////////////////////////////////////////////////


#include "Mathf.h"
#include "LuaBind.h"

using ce::Mathf;


/* Author: Rasmus Andersson */
// Templated clamping method
template <typename T>
T ce::Mathf<T>::Clamp(T value, T maxValue, T minValue)
{
    if (value > maxValue)
    {
        value = maxValue;
    }
    else if (value < minValue)
    {
        value = minValue;
    }

    return value;
}


/* Author: Oskar Svensson*/
// Templated linear interpolation method
template <typename T>
T ce::Mathf<T>::Lerp(T value, T goal, T step)
{
    return value + (goal - value) * step;
}

template <typename T>
void ce::Mathf<T>::DoBind(lua_State * L, const std::string& s)
{
    luabridge::getGlobalNamespace(L)
        .beginNamespace("Chef")
            .beginClass<ce::Mathf<T>>(std::string("Math" + s).c_str())
                .addStaticFunction(std::string("Clamp" + s).c_str(), &ce::Mathf<T>::Clamp)
                .addStaticFunction(std::string("Lerp" + s).c_str(), &ce::Mathf<T>::Lerp)
            .endClass()
        .endNamespace();
              
}

template class Mathf<int>;
template class Mathf<signed int>;
template class Mathf<short int>;
template class Mathf<unsigned short int>;
template class Mathf<signed short int>;
template class Mathf<long int>;
template class Mathf<signed long int>;
template class Mathf<unsigned long int>;

template class Mathf<float>;
template class Mathf<double>;
template class Mathf<long double>;
