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


#include "LuaComponent.h"

#include "LuaBind.h"

#include <iostream>

using ce::LuaComponent;


void LuaComponent::SetRef(luabridge::LuaRef* ref)
{
    this->ref = ref;

    // Calls the Awake function in the lua script, if there is one
    if ((*ref)["Awake"].isFunction())
    {
        (*ref)["Awake"]((*ref));
    }       

    // Sets the Start and Update methods of the Lua Script
    if ((*ref)["Start"].isFunction())
    {
        startFunc = std::make_unique<luabridge::LuaRef>((*ref)["Start"]);
    }
    if ((*ref)["Update"].isFunction())
    {
        updateFunc = std::make_unique<luabridge::LuaRef>((*ref)["Update"]);
    }
    

    // Sets all the Collision Event methods of the Lua Script
    if ((*ref)["OnCollisionEnter"].isFunction())
	{
        onCollisionEnterFunc = std::make_unique<luabridge::LuaRef>((*ref)["OnCollisionEnter"]);
	}
    if ((*ref)["OnCollisionExit"].isFunction())
    {
        onCollisionExitFunc = std::make_unique<luabridge::LuaRef>((*ref)["OnCollisionExit"]);
    }
	if ((*ref)["OnCollisionStay"].isFunction())
	{
		onCollisionStayFunc = std::make_unique<luabridge::LuaRef>((*ref)["OnCollisionStay"]);
	}
    if ((*ref)["OnTriggerEnter"].isFunction())
    {
        onTriggerEnterFunc = std::make_unique<luabridge::LuaRef>((*ref)["OnTriggerEnter"]);
    }
    if ((*ref)["OnTriggerExit"].isFunction())
    {
        onTriggerExitFunc = std::make_unique<luabridge::LuaRef>((*ref)["OnTriggerExit"]);
    }
	if ((*ref)["OnTriggerStay"].isFunction())
	{
		onTriggerStayFunc = std::make_unique<luabridge::LuaRef>((*ref)["OnTriggerStay"]);
	}

}


LuaComponent::~LuaComponent()
{
}

// All the "Lua Functions" are methods that call on functions in Lua using LuaRefs
#pragma region Lua Functions
void LuaComponent::Start()
{
    if (startFunc)
    {
        (*startFunc)(*ref);
    }
}


void LuaComponent::Update()
{
    if (updateFunc)
    {
        (*updateFunc)(*ref);
    }
}

void ce::LuaComponent::OnCollisionEnter(ce::Collider * collider)
{
    if (onCollisionEnterFunc)
    {
        (*onCollisionEnterFunc)(*ref, collider);
    }
}

void ce::LuaComponent::OnCollisionExit(ce::Collider * collider)
{
    if (onCollisionExitFunc)
    {
        (*onCollisionExitFunc)(*ref, collider);
    }
}

void ce::LuaComponent::OnCollisionStay(ce::Collider * collider)
{
	if (onCollisionStayFunc)
	{
		(*onCollisionStayFunc)(*ref, collider);
	}
}

void ce::LuaComponent::OnTriggerEnter(ce::Collider * collider)
{
    if (onTriggerEnterFunc)
    {
        (*onTriggerEnterFunc)(*ref, collider);
    }
}

void ce::LuaComponent::OnTriggerExit(ce::Collider * collider)
{
    if (onTriggerExitFunc)
    {
        (*onTriggerExitFunc)(*ref, collider);
    }
}

void ce::LuaComponent::OnTriggerStay(ce::Collider * collider)
{
	if (onTriggerStayFunc)
	{
		(*onTriggerStayFunc)(*ref, collider);
	}
}
#pragma endregion

luabridge::LuaRef LuaComponent::LoadComponent(luabridge::LuaRef component)
{
    // Creates an empty table in the same state as the component we want to copy
    luabridge::LuaRef newComponent = luabridge::newTable(component.state());

    ce::LuaKeyValue* keys = getKeyValueMap(component);

    // Loops through all the members with string keys in the table
    for (auto pair : keys->stringKeys)
    {
        // Sets a key on our new, copied table to have the correct coresponding value
        newComponent[pair.first] = pair.second;
    }
    // Does the same with the number keys
    for (auto pair : keys->numberKeys)
    {
        newComponent[pair.first] = pair.second;
    }

    delete keys;

    return newComponent;
}


ce::LuaKeyValue* LuaComponent::getKeyValueMap(const luabridge::LuaRef& table)
{
    ce::LuaKeyValue* keys = new ce::LuaKeyValue();

    // Returns immediately if their isn't anything on the LuaRef
    if (table.isNil()) { return keys; }

    // Gets the state of the table and pushes it up again so it's on the top of the stack
    auto L = table.state();
    push(L, table);

    // Pushes nil so lua_next takes it from the stack and instead put's (k, v) (the pairs in the table) on the stack
    lua_pushnil(L);
    // Checks if there is something on (-2) which is the first key
    while (lua_next(L, -2) != 0) 
    {        
        if (lua_isnumber(L, -2))
        {
            // Stores the number key and it's value in the number map
            keys->numberKeys.emplace(lua_tonumber(L, -2), luabridge::LuaRef::fromStack(L, -1));
        }
        // Checks if the key was a string
        else if (lua_isstring(L, -2)) 
        {
                // Stores the string key and it's value in the string map
                keys->stringKeys.emplace(lua_tostring(L, -2), luabridge::LuaRef::fromStack(L, -1));
        }

        // Removes the value we just checked so lua_next will go to the next one
        lua_pop(L, 1);
    }
    // Removes the whole copied table;
    lua_pop(L, 1); 

    return keys;
}


void ce::LuaComponent::DoBind(lua_State * L)
{
    luabridge::getGlobalNamespace(L)
        .beginNamespace("Chef")
            .addFunction("LoadComponent", &LuaComponent::LoadComponent)
            .deriveClass<LuaComponent, Component>("LuaComponent")
            .endClass()
        .endNamespace();
}
