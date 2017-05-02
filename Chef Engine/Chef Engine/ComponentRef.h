#pragma once

#include "LuaBridgeBinder.h"
#include "Component.h"
#include <map>
#include <functional>

namespace ce
{
	class ComponentRef
	{
		ComponentRef();

		// Befriends the templated Bind function so it can access our protected functions
		friend void LuaBridgeBinder::Bind<ce::ComponentRef>(lua_State*);

	public:
		static std::map<int, std::function<ce::Component(void)>> componentConstructMap;

	private:
		static void BindComponentID();

		// Binds all relevant members of this class with LuaBridge
		static void DoBind(lua_State* L);

		static int componentIDCounter;


	};
}
