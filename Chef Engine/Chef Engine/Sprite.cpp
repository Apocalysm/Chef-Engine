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


#include "Sprite.h"
#include "Transform.h"
#include "GameObject.h"

#include "DrawEventManager.h"
#include "ResourceManager.h"
#include "Texture.h"

#include "LuaBind.h"

#include <SFML\Graphics.hpp>

using ce::Sprite;

Sprite::Sprite()
{
	sprite = new sf::Sprite();
}


Sprite::Sprite(const int newDrawOrder)
{
	sprite = new sf::Sprite();

	drawOrder = newDrawOrder;
}


Sprite::~Sprite()
{
	delete sprite;

	texture->DecrementUseCount();
}


void Sprite::Update()
{
	// Updates psition, scale and rotation depending on the set values in the transform
	sprite->setPosition(transform->GetPosition().ToSfVector2());
	sprite->setRotation(transform->GetRotation());
	sprite->setScale(transform->GetScale().ToSfVector2());
}


void Sprite::SetSprite(const std::string& fileName)
{
	texture = (ce::Texture*)ce::ResourceManager::GetResource(fileName);

	sprite->setTexture(*texture->GetTexture());
    sprite->setTextureRect(sf::IntRect(sf::Vector2i(0,0), (sf::Vector2i)texture->GetTexture()->getSize()));
	sprite->setPosition(transform->GetPosition().ToSfVector2());
}

void ce::Sprite::ChangeSprite(sf::Sprite* sprite)
{
	delete this->sprite; 
	this->sprite = sprite;
}


void Sprite::SetOrigin(const float x, const float y)
{
	sprite->setOrigin(x, y);
}


void Sprite::SetOrigin(const sf::Vector2f newOrigin)
{
	sprite->setOrigin(newOrigin);
}


void Sprite::SetColor(const sf::Color& color)
{
	sprite->setColor(color);
}


void Sprite::SetColor(const int r, const int g, const int b, const int a)
{
	sprite->setColor(sf::Color(r, g, b, a));
}


sf::Sprite* Sprite::GetSprite() const
{
	return sprite;
}


sf::Drawable* ce::Sprite::GetDrawable() const
{
	return sprite;
}


const ce::Vec2f& Sprite::GetOrigin() const
{
	return ce::Vec2f(sprite->getOrigin());
}


sf::Color Sprite::GetColor() const
{
	return sprite->getColor();
}


void Sprite::DoBind(lua_State * L)
{
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Chef")
			.deriveClass<Sprite, Component>("Sprite")
				.addConstructor<void(*)(void)>()
                .addFunction("SetSprite", &Sprite::SetSprite)
				.addProperty("sprite", &Sprite::GetSprite, &Sprite::ChangeSprite)
				.addProperty("origin", &Sprite::GetOrigin, &Sprite::SetOrigin)
				.addProperty("color", &Sprite::GetColor, &Sprite::SetColor)
				.addProperty("drawOrder", &Sprite::GetDrawOrder, &Sprite::SetDrawOrder)
			.endClass()
		.endNamespace();
}