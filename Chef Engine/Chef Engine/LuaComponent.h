#pragma once

#include "Component.h"

#include <LuaBridge.h>

#include <memory>
#include <vector>
#include <string>

namespace ce
{
    class LuaComponent : public ce::Component
    {

    public:
        LuaComponent();
        ~LuaComponent();

        void Start() override;
        void Update() override;

        void LoadScript(lua_State* L, const std::string* scriptFilename, const std::string* tableName);

    private:

        // Points to the Component 'Start' method, in a lua script
        std::unique_ptr<luabridge::LuaRef> startFunc;
        // Points to the Component 'Update' method, in a lua script
        std::unique_ptr<luabridge::LuaRef> updateFunc;

        // Holds all non-standard members of our lua component scripts
        std::vector<std::unique_ptr<luabridge::LuaRef>> luaRefs;
    };
}

