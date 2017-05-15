#include "LuaComponent.h"

#include <iostream>

using ce::LuaComponent;
 

LuaComponent::LuaComponent(luabridge::LuaRef ref)
{
    *instance = ref;
}


LuaComponent::~LuaComponent()
{
}


void LuaComponent::Start()
{
    if (startFunc != nullptr)
    {
        (*startFunc)();
    }
}


void LuaComponent::Update()
{
    if (updateFunc != nullptr)
    {
        (*updateFunc)();
    }
}


void LuaComponent::LoadScript(lua_State* L, const std::string* scriptPath, const std::string* tableName)
{
    // If luaL_dofile doesn't find anything at the scriptPath, we get an error
    if (luaL_dofile(L, scriptPath->c_str()))
    {
        std::cerr << lua_tostring(L, -1) << std::endl;
    }

    // Gets the specified table to see if it exists, if not, we get an error
    luabridge::LuaRef table = luabridge::getGlobal(L, tableName->c_str());

    if (!table.isTable())
    {
        std::cerr << lua_tostring(L, -1) << std::endl;
    }


    // Checks if a function called "Start" exists in the table 
    if (table["Start"].isFunction())
    {
        // If it is, we add it to the startFunc pointer
        startFunc = std::make_unique<luabridge::LuaRef>(table["Start"]);
    }
    else
    {
        // If not, we make sure it's pointing to null
        startFunc = nullptr;
    }

    // Checks if a function called "Update" exists in the table 
    if (table["Update"].isFunction())
    {
        // If it is, we add it to the updateFunc pointer
        updateFunc = std::make_unique<luabridge::LuaRef>(table["Update"]);
    }
    else
    {
        // If not, we make sure it's pointing to null
        updateFunc = nullptr;
    }
}
