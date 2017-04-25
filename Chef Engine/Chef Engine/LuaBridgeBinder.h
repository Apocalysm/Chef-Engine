#pragma once
#include <lua.hpp>
#include <LuaBridge.h>

class LuaBridgeBinder
{
public:

	// Creates a templated Bind function
	template<typename T>
	static void Bind(lua_State* L);

	static void BindAll();
};

