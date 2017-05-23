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
    startFunc = std::make_unique<luabridge::LuaRef>(ref["Start"]);
    updateFunc = std::make_unique<luabridge::LuaRef>(ref["Update"]);
}


LuaComponent::~LuaComponent()
{
}


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


luabridge::LuaRef LuaComponent::LoadComponent(luabridge::LuaRef component)
{
    // Creates an empty table in the same state as the component we want to copy
    luabridge::LuaRef newComponent = luabridge::newTable(component.state());
    
    // Loops through all the members of the component-table we want to copy 
    for (auto pair : getKeyValueMap(component))
    {
        // Sets a key on our new, copied table to have the correct coresponding value
        newComponent[pair.first] = pair.second;
    }

    return newComponent;
}


std::unordered_map<std::string, luabridge::LuaRef> LuaComponent::getKeyValueMap(const luabridge::LuaRef& table)
{
    std::unordered_map<std::string, luabridge::LuaRef> result;
    if (table.isNil()) { return result; }

    auto L = table.state();
    push(L, table); // push table

    lua_pushnil(L);  // push nil, so lua_next removes it from stack and puts (k, v) on stack
    while (lua_next(L, -2) != 0) { // -2, because we have table at -1
        if (lua_isstring(L, -2)) { // only store stuff with string keys
            result.emplace(lua_tostring(L, -2), luabridge::LuaRef::fromStack(L, -1));
        }
        lua_pop(L, 1); // remove value, keep key for lua_next
    }

    lua_pop(L, 1); // pop table
    return result;
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
