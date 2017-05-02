#pragma once
#include <lua.hpp>
#include <LuaBridge.h>
#include <vector>
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
		static void LoadLua(lua_State* L, const std::string& path);
		
	};
}

