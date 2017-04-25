#include "LuaBridgeBinder.h"

#include "Object.h"

// Linking a library through code
#pragma comment(lib, "lua53.lib")

// Creates a templated Bind function
template<typename T>
void LuaBridgeBinder::Bind(lua_State* L)
{
	T::DoBind(L);
}

// Call this to call the Bind method in all classes written here
void LuaBridgeBinder::BindAll()
{
	// Create a new lua_State and open default Lua-libraries
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	// Here you put all the method calls for the classes you want to bind
	Bind<ce::Object>(L);

	
}
