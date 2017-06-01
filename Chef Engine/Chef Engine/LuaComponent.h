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


#pragma once
#include "Component.h"

#include "LuaBridgeBinder.h"

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

namespace luabridge
{
    class LuaRef;
}

struct lua_State;

namespace ce
{
    class Collider;
    class LuaBridgeBinder;

    struct LuaKeyValue
    {
        std::unordered_map<std::string, luabridge::LuaRef> stringKeys;
        std::unordered_map<int, luabridge::LuaRef> numberKeys;
    };

    class LuaComponent : public ce::Component
    {
        // Befriends the templated Bind function so it can access our protected functions
        friend void LuaBridgeBinder::Bind<ce::LuaComponent>(lua_State*);

    public:
        ~LuaComponent();

        void Start() override;
        void Update() override;

        void OnCollisionEnter(ce::Collider* collider);
        void OnCollisionExit(ce::Collider* collider);
		void OnCollisionStay(ce::Collider* collider);
        void OnTriggerEnter(ce::Collider* collider);
        void OnTriggerExit(ce::Collider* collider);
		void OnTriggerStay(ce::Collider* collider);

        void SetRef(luabridge::LuaRef* ref);

    private:
        friend class ce::GameObject;

        // Our actual component instance where all values and such are stored
        luabridge::LuaRef* ref;

        // Points to the Component 'Start' method, in a lua script
        std::unique_ptr<luabridge::LuaRef> startFunc;
        // Points to the Component 'Update' method, in a lua script
        std::unique_ptr<luabridge::LuaRef> updateFunc;

        // Points to the Component 'OnCollisionEnter' method, in a lua script
        std::unique_ptr<luabridge::LuaRef> onCollisionEnterFunc;
        // Points to the Component 'OnCollisionExit' method, in a lua script
        std::unique_ptr<luabridge::LuaRef> onCollisionExitFunc;
		// Points to the Component 'OnCollisionStay' method in lua script
		std::unique_ptr<luabridge::LuaRef> onCollisionStayFunc;
        // Points to the Component 'OnTriggerEnter' method, in a lua script
        std::unique_ptr<luabridge::LuaRef> onTriggerEnterFunc;
        // Points to the Component 'OnTriggerExit' method, in a lua script
        std::unique_ptr<luabridge::LuaRef> onTriggerExitFunc;
		// Points to the Component 'OnTriggerStay' method in lua script
		std::unique_ptr<luabridge::LuaRef> onTriggerStayFunc;


        // Takes in a table and creates a new table and copies all of that tables members and puts them in the new one
        static luabridge::LuaRef LoadComponent(luabridge::LuaRef component);

        static void DoBind(lua_State* L);
        
        static LuaKeyValue* getKeyValueMap(const luabridge::LuaRef & table);
    };
}

