#pragma once

#include "Component.h"

#include <LuaBridge.h>

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

// Linking a library through code
#pragma comment(lib, "lua53.lib")

namespace ce
{
    class LuaComponent : public ce::Component
    {
    public:
        LuaComponent(luabridge::LuaRef ref);
        ~LuaComponent();

        void Start() override;
        void Update() override;

        void LoadScript(lua_State* L, const std::string* scriptFilename, const std::string* tableName);

    private:

        // Our actual component instance where all values and such are stored
        std::unique_ptr<luabridge::LuaRef> instance;

        // Points to the Component 'Start' method, in a lua script
        std::unique_ptr<luabridge::LuaRef> startFunc;
        // Points to the Component 'Update' method, in a lua script
        std::unique_ptr<luabridge::LuaRef> updateFunc;
    };
}

