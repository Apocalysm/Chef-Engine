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


#include "DrawableComponent.h"
#include "DrawEventManager.h"
#include "GameObject.h"

#include "LuaBind.h"

ce::DrawableComponent::DrawableComponent()
{
	isNew = true;

	drawOrder = 0;
}


ce::DrawableComponent::~DrawableComponent()
{
	ce::DrawEventManager::RemoveDrawable(this);
}


sf::Drawable* ce::DrawableComponent::GetDrawable() const
{
	return nullptr;
}


void ce::DrawableComponent::SetDrawOrder(const int drawOrder)
{
	ce::DrawEventManager::MoveDrawable(this, drawOrder);

	this->drawOrder = drawOrder;
}


int ce::DrawableComponent::GetDrawOrder() const
{
	return drawOrder;
}


void ce::DrawableComponent::SetGameObject(GameObject* gameObject)
{
	this->gameObject = gameObject;

	// Gets the transform of the owner of this sprite-component
	transform = gameObject->GetTransform();

	ce::DrawEventManager::AddDrawable(this);
}


void ce::DrawableComponent::DoBind(lua_State* L)
{
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Chef")
			.beginClass<ce::DrawableComponent>("DrawableComponent")
				.addConstructor<void(*) (void)>()
				.addProperty("drawOrder", &DrawableComponent::GetDrawOrder, &DrawableComponent::SetDrawOrder)
			.endClass()
		.endNamespace();
}