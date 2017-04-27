#pragma once

#include "LuaBridgeBinder.h"
#include "Component.h"
#include <typeinfo>

namespace ce
{
	class ComponentRef
	{
		// Befriends the templated Bind function so it can access our protected functions
		friend void LuaBridgeBinder::Bind<ce::ComponentRef>(lua_State*);

	public:
		
		static std::map<int, ce::Component()> compConstructMap;

		// Gets the typeid().hash_code of the specified type
		template <typename T> int GetHashCode();

	private:
		// Binds all relevant members of this class with LuaBridge
		static void DoBind(lua_State* L);
	};
}

// Gets the typeid().hash_code of the specified type
template <typename T> int GetHashCode()
{
	return typeid(T).hash_code();
}
