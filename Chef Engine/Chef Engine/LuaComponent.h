#pragma once

#include "Component.h"
#include "LuaBridgeBinder.h"
#include "Collider.h"

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

        void OnCollisionEnter(ce::Collider* collider);
        void OnCollisionExit(ce::Collider* collider);
		void OnCollisionStay(ce::Collider* collider);
        void OnTriggerEnter(ce::Collider* collider);
        void OnTriggerExit(ce::Collider* collider);
		void OnTriggerStay(ce::Collider* collider);

    private:
        friend class ce::GameObject;

        // Our actual component instance where all values and such are stored
        luabridge::LuaRef ref;

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
        
        static std::pair<std::unordered_map<std::string, luabridge::LuaRef>, std::unordered_map<int, luabridge::LuaRef>> getKeyValueMap(const luabridge::LuaRef & table);
    };
}

