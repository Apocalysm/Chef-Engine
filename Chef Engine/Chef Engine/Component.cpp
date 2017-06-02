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


#include "Component.h"

#include "GameObject.h"

#include <lua.hpp>
#include <LuaBridge.h>

#include <typeinfo>


ce::Component::Component() :
    isNew(true), gameObject(nullptr), enabled(true)
{

}


ce::Component::~Component()
{
}


void ce::Component::Start()
{
}


void ce::Component::Update()
{
}


int ce::Component::GetID() const
{
	return this->ID;
}


void ce::Component::SetID(int ID)
{
	this->ID = ID;
}


void ce::Component::SetEnabled(bool enabled)
{
	this->enabled = enabled;
}


bool ce::Component::GetEnabled() const
{
	return this->enabled;
}

void ce::Component::SetIsNew(bool isNew)
{
    this->isNew = isNew;
}

bool ce::Component::GetIsNew() const
{
    return this->isNew;
}


ce::GameObject* ce::Component::GetGameObject() const
{
	return gameObject;
}


void ce::Component::SetGameObject(GameObject * gameObject)
{
	this->gameObject = gameObject;
}


// The == operator of Component compares the ID of the component
bool ce::Component::operator==(const Component& other)
{
	if (this->ID == other.ID)
	{
		return true;
	}

	return false;
}

void ce::Component::DoBind(lua_State* L)
{
    luabridge::getGlobalNamespace(L)
        .beginNamespace("Chef")
            .beginClass<ce::Component>("Component")
                .addConstructor<void (*) (void)>()
                .addProperty("gameObject", &Component::GetGameObject)
                .addProperty("enabled", &Component::GetEnabled, &Component::SetEnabled)
            .endClass()
        .endNamespace();
}
