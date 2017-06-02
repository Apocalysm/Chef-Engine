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
// Author: Dennis Karlsson
//
////////////////////////////////////////////////////////////


#pragma once

#include "Component.h"

namespace sf
{
	class Drawable;
}

namespace ce
{
	class Transform;

	class DrawableComponent : public Component
	{
		// Befriends the templated Bind function so it can access our protected functions
		friend void LuaBridgeBinder::Bind<ce::DrawableComponent>(lua_State*);

		friend class DrawEventManager;

	public:
		DrawableComponent();
		~DrawableComponent();

		virtual sf::Drawable* GetDrawable() const;
		
		void SetDrawOrder(const int drawOrder);

		int GetDrawOrder() const;

		void SetGameObject(GameObject* gameObject);

	protected:
		int drawOrder;

		bool isNew;

		// The transform of this components GameObject
		ce::Transform* transform;

	private:
		// Binds parts of this script to Lua
		static void DoBind(lua_State* L);
	};
}