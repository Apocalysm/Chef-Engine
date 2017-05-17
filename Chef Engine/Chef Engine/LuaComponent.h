#pragma once

#include "Component.h"
#include "LuaBridgeBinder.h"

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

namespace ce
{
    class LuaComponent : public ce::Component
    {
        // Befriends the templated Bind function so it can access our protected functions
        friend void LuaBridgeBinder::Bind<ce::LuaComponent>(lua_State*);

    public:
        LuaComponent(luabridge::LuaRef ref);
        ~LuaComponent();

        void Start() override;
        void Update() override;

        void LoadScript(lua_State* L, const std::string* scriptFilename, const std::string* tableName);

    private:
        friend class ce::GameObject;

        // Our actual component instance where all values and such are stored
        std::unique_ptr<luabridge::LuaRef> ref;

        // Points to the Component 'Start' method, in a lua script
        std::unique_ptr<luabridge::LuaRef> startFunc;
        // Points to the Component 'Update' method, in a lua script
        std::unique_ptr<luabridge::LuaRef> updateFunc;

        // Takes in a table and creates a new table and copies all of that tables members and puts them in the new one
        static luabridge::LuaRef LoadComponent(luabridge::LuaRef component);

        static void DoBind(lua_State* L);
        
        static std::unordered_map<std::string, luabridge::LuaRef> getKeyValueMap(const luabridge::LuaRef & table);
    };
}

