#pragma once
#include <SFML\Graphics.hpp>
#include "LuaBridgeBinder.h"

namespace ce
{
    // In this class we bind SFML classes such as sf::Vector, with LuaBridge
    class SFML_Bind
    {
        // Befriends the templated Bind function so it can access our protected functions
        friend void LuaBridgeBinder::Bind<ce::SFML_Bind>(lua_State*);

    private:

        static void DoBind(lua_State* L)
        {
            luabridge::getGlobalNamespace(L)
                .beginNamespace("Chef")
                // Binds the three templated types of sf::Vector2
                    .beginClass<sf::Vector2f>("Vector2f")
                        .addConstructor<void(*)(float, float)>()
                        .addData("x", &sf::Vector2f::x)
                        .addData("y", &sf::Vector2f::y)
                    .endClass()
                    .beginClass<sf::Vector2i>("Vector2i")
                        .addConstructor<void(*)(int, int)>()
                        .addData("x", &sf::Vector2i::x)
                        .addData("y", &sf::Vector2i::y)
                    .endClass()
                    .beginClass<sf::Vector2u>("Vector2u")
                        .addConstructor<void(*)(unsigned, unsigned)>()
                        .addData("x", &sf::Vector2u::x)
                        .addData("y", &sf::Vector2u::y)
                    .endClass()
                
                .endNamespace();

        }
    };
}
