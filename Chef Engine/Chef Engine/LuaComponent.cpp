#include "LuaComponent.h"

#include <iostream>

using ce::LuaComponent;


LuaComponent::LuaComponent()
{
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


    // Checks if "Start" is a function in the Lua Script
    if (table["Start"].isFunction())
    {
        // If it is, we add it to the startFunc pointer
        startFunc = std::make_unique<luabridge::LuaRef>(table["Start"]);
    }
    else
    {
        // If it is not, we set it to null so the Start method in this class will ignore it
        startFunc = nullptr;
    }

    // We repeat the same actions with the Update function as we did with Start just above
    if (table["Update"].isFunction())
    {
        updateFunc = std::make_unique<luabridge::LuaRef>(table["Update"]);
    }
    else
    {
        updateFunc = nullptr;
    }


}
