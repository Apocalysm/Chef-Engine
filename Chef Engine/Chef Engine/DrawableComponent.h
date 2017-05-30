#pragma once

#include "Component.h"

namespace sf
{
	class Drawable;
}

namespace ce
{
	class DrawableComponent : public Component
	{
		// Befriends the templated Bind function so it can access our protected functions
		friend void LuaBridgeBinder::Bind<ce::DrawableComponent>(lua_State*);

	public:
		virtual sf::Drawable* GetDrawable() const;
		
		void SetDrawOrder(const int drawOrder);
		int GetDrawOrder() const;

	protected:
		friend class DrawEventManager;
		int drawOrder;

	private:
		// Binds parts of this script to Lua
		static void DoBind(lua_State* L);
	};
}