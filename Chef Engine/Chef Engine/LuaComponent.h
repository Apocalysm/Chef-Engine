#pragma once
#include "Component.h"

#include <LuaBridge.h>
#include <memory>

namespace ce
{
    class LuaComponent : public ce::Component
    {

    public:
        LuaComponent();
        ~LuaComponent();

        void Start();
        void Update();

    private:

        std::unique_ptr<luabridge::LuaRef> startFunc;
        std::unique_ptr<luabridge::LuaRef> updateFunc;
    };
}

