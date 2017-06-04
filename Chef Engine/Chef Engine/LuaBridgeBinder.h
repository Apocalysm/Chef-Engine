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

////////////////////////////////////////////////////////////
//
// Author: Oskar Svensson
//
////////////////////////////////////////////////////////////

#pragma once
#include "Common.h"
#include <vector>
#include <map>
#include <string>
#include <memory>

namespace luabridge
{
    class LuaRef;
}

struct lua_State;

namespace ce
{
	class LuaBridgeBinder
	{
	public:

		// Creates a templated Bind function
		template<typename T>
        static void Bind(lua_State* L);
		template<typename T>
		static void Bind(lua_State* L, const std::string& suffix);

        CHEF_API static void BindAll();

        CHEF_API static std::unique_ptr<luabridge::LuaRef> mainFunc;

        // Loads Lua files
		static void LoadLua(lua_State* L, const std::string& table, const std::string& path);

        static lua_State* L;

	private:
        static void RegisterComponent(luabridge::LuaRef ref);
        
        // This is for registering components from lua
        static int componentIDCounter;

	};
}

