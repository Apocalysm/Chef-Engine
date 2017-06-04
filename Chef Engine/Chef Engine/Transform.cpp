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


#include "Transform.h"

#include "GameObject.h"
#include "Collider.h"

#include "LuaBind.h"

#include <SFML\System\Vector2.hpp>

using ce::Transform;

// Default Constructor
Transform::Transform()
    : position(0.0f, 0.0f)
{
	//position = ce::Vec2f(0.0f, 0.0f);
	SetRotation(0);
	SetScale(1, 1);
}

ce::Transform::Transform(const ce::Vec2f& position, const float rotation, const ce::Vec2f& scale)
{
    SetPosition(position);
    SetRotation(rotation);
    SetScale(scale);
}

Transform::~Transform()
{
}


void Transform::Start()
{
}


void ce::Transform::Update()
{

}


// Overload for SetPosition with floating numbers instead of a sf::Vector2f
void Transform::SetPosition(const float x, const float y)
{
	SetPosition(ce::Vec2f(x, y));
}


void Transform::SetPosition(const ce::Vec2f& newPosition)
{
	position = newPosition;
}


const ce::Vec2f& Transform::GetPosition() const
{
	return position;
}


void ce::Transform::Move(const ce::Vec2f& movement)
{
	position += movement;
}


void Transform::SetRotation(float newRotation)
{
	rotation = newRotation;
}


float ce::Transform::GetRotation() const
{
	return rotation;
}


// Adds to the rotation with the specified angle
void Transform::Rotate(float angle)
{
	rotation += angle;
}


// Overload for SetScale with floats instead of a sf::Vector2f
void Transform::SetScale(const float x, const float y)
{
	SetScale(Vec2f(x, y));
}


const ce::Vec2f& ce::Transform::GetScale() const
{
	return scale;
}


void Transform::SetScale(const ce::Vec2f& newScale)
{
	scale = newScale;
}


void ce::Transform::SetGameObject(GameObject * gameObject)
{
	this->gameObject = gameObject;
}


void Transform::DoBind(lua_State * L)
{
    luabridge::getGlobalNamespace(L)
        .beginNamespace("Chef")
            .deriveClass<Transform, Component>("Transform")
                .addConstructor<void(*)(void)>()
                .addProperty("position", &Transform::GetPosition, &Transform::SetPosition)
                .addProperty("rotation", &Transform::GetRotation, &Transform::SetRotation)
                .addProperty("scale", &Transform::GetScale, &Transform::SetScale)
                .addFunction("Move", &Transform::Move)
                .addFunction("Rotate", &Transform::Rotate)
            .endClass()
        .endNamespace();
}