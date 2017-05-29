#include "LuaComponent.h"

#include <iostream>

using ce::LuaComponent;


LuaComponent::LuaComponent(luabridge::LuaRef ref) :
    ref(ref.state())
{
    this->ref = ref;

    // Calls the Awake function in the lua script, if there is one
    if (ref["Awake"].isFunction())
    {
        ref["Awake"](ref);
    }

    // Sets the Start and Update methods of the Lua Script
    if (ref["Start"].isFunction())
    {
        startFunc = std::make_unique<luabridge::LuaRef>(ref["Start"]);
    }
    if (ref["Update"].isFunction())
    {
        updateFunc = std::make_unique<luabridge::LuaRef>(ref["Update"]);
    }


    // Sets all the Collision Event methods of the Lua Script
    if (ref["OnCollisionEnter"].isFunction())
    {
        onCollisionEnterFunc = std::make_unique<luabridge::LuaRef>(ref["OnCollisionEnter"]);
    }
    if (ref["OnCollisionExit"].isFunction())
    {
        onCollisionExitFunc = std::make_unique<luabridge::LuaRef>(ref["OnCollisionExit"]);
    }

    if (ref["OnTriggerEnter"].isFunction())
    {
        onTriggerEnterFunc = std::make_unique<luabridge::LuaRef>(ref["OnTriggerEnter"]);
    }
    if (ref["OnTriggerExit"].isFunction())
    {
        onTriggerExitFunc = std::make_unique<luabridge::LuaRef>(ref["OnTriggerExit"]);
    }

}


LuaComponent::~LuaComponent()
{
}

// All the "Lua Functions" are methods that call on functions in Lua using LuaRefs
#pragma region Lua Functions
void LuaComponent::Start()
{
    if (startFunc != nullptr)
    {
        (*startFunc)(ref);
    }
}


void LuaComponent::Update()
{
    if (updateFunc != nullptr)
    {
        (*updateFunc)(ref);
    }
}

void ce::LuaComponent::OnCollisionEnter(ce::Collider * collider)
{
    if (onCollisionEnterFunc != nullptr)
    {
        (*onCollisionEnterFunc)(ref, collider);
    }
}

void ce::LuaComponent::OnCollisionExit(ce::Collider * collider)
{
    if (onCollisionExitFunc != nullptr)
    {
        (*onCollisionExitFunc)(ref, collider);
    }
}

void ce::LuaComponent::OnTriggerEnter(ce::Collider * collider)
{
    if (onTriggerEnterFunc != nullptr)
    {
        (*onTriggerEnterFunc)(ref, collider);
    }
}

void ce::LuaComponent::OnTriggerExit(ce::Collider * collider)
{
    if (onTriggerExitFunc != nullptr)
    {
        (*onTriggerExitFunc)(ref, collider);
    }
}
#pragma endregion

luabridge::LuaRef LuaComponent::LoadComponent(luabridge::LuaRef component)
{
    // Creates an empty table in the same state as the component we want to copy
    luabridge::LuaRef newComponent = luabridge::newTable(component.state());
    
    // Loops through all the members of the component-table we want to copy 
    for (auto pair : getKeyValueMap(component).second)
    {
        // Sets a key on our new, copied table to have the correct coresponding value
        newComponent[pair.first] = pair.second;
    }

    return newComponent;
}


std::pair<std::unordered_map<std::string, luabridge::LuaRef>, std::unordered_map<int, luabridge::LuaRef>> 
LuaComponent::getKeyValueMap(const luabridge::LuaRef& table)
{
    std::unordered_map<std::string, luabridge::LuaRef> string_result;
    std::unordered_map<int, luabridge::LuaRef> number_result;

    // Returns immediately if their isn't anything on the LuaRef
    if (table.isNil()) { return std::make_pair(string_result, number_result); }

    // Gets the state of the table and pushes it up again so it's on the top of the stack
    auto L = table.state();
    push(L, table);

    // Pushes nil so lua_next takes it from the stack and instead put's (k, v) (the pairs in the table) on the stack
    lua_pushnil(L);
    // Checks if there is something on (-2) which is the first key
    while (lua_next(L, -2) != 0) 
    {
        // Checks if the key was a string
        if (lua_isstring(L, -2)) 
        { 
            // Stores the string key and it's value in the unordered_map
            string_result.emplace(lua_tostring(L, -2), luabridge::LuaRef::fromStack(L, -1));
        }
        else if (lua_isnumber(L, -2))
        {
            number_result.emplace(lua_tonumber(L, -2), luabridge::LuaRef::fromStack(L, -1));
        }
        // Removes the value we just checked so lua_next will go to the next one
        lua_pop(L, 1);
    }
    // Removes the whole copied table;
    lua_pop(L, 1); 

    return std::make_pair(string_result, number_result);
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
