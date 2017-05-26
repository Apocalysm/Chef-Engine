#pragma once
#include <lua.hpp>
#include <LuaBridge.h>

#include <vector>
#include <map>
#include <string>


namespace ce
{
	class LuaBridgeBinder
	{
	public:

		// Creates a templated Bind function
		template<typename T>
		static void Bind(lua_State* L);

		static void BindAll();

	private:
        // Loads a Lua 
		static void LoadLua(lua_State* L, const std::string& table, const std::string& path);

        static void RegisterComponent(luabridge::LuaRef ref);
        
        // This is for registering components from lua
        static int componentIDCounter;

        //static std::map<luabridge::LuaRef
	};
}

