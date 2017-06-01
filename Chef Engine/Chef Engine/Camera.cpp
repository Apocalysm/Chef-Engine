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


#include "Camera.h"

#include "GameObject.h"
#include "Transform.h"

#include "MapHandler.h"
#include "Mathf.h"
#include "LuaBind.h"

#include <SFML\Graphics.hpp>

using ce::Camera;

Camera* Camera::main;
sf::RenderWindow* Camera::window;

Camera::Camera()
    : zoom(1)
    , follow(false)
    , view(new sf::View())
{
    if (main == nullptr)
    {
        main = this;
        window->setView(*this->GetView());
    }
}


Camera::~Camera()
{
}


void ce::Camera::SetSize(const ce::Vec2f& size)
{
	this->size = size;
	view->setSize(size.ToSfVector2());
}


const ce::Vec2f& ce::Camera::GetSize() const
{
	return size;
}

void ce::Camera::SetZoom(float zoom)
{
	view->zoom(zoom);
	this->zoom *= zoom;
}

float ce::Camera::GetZoom() const
{
	return 0.0f;
}


const sf::View* ce::Camera::GetView() const
{
	return view;
}


void ce::Camera::SetCenter(const ce::Vec2f& center)
{
	this->center = center;
	view->setCenter(center.ToSfVector2());
}


const ce::Vec2f& ce::Camera::GetCenter() const
{
	return this->center;
}


bool ce::Camera::GetFollow() const
{
	return follow;
}


void ce::Camera::SetFollow(const bool & follow)
{
	this->follow = follow;
}


void ce::Camera::UpdateCamera()
{
    if (follow)
    {
        center = gameObject->GetTransform()->GetPosition();
        view->setCenter(center.ToSfVector2());
    }

    mapSize = ce::Vec2i(ce::MapHandler::GetMapSize());

    ce::Vec2f clampedCenter = center.ToSfVector2();
    
    if (mapSize.x > 0 && mapSize.y > 0)
    {
        clampedCenter = ce::Vec2f(ce::Mathf::Clamp<float>(view->getCenter().x, mapSize.x - (size.x / 2) * zoom, 0 + (size.x / 2) * zoom),
                                  ce::Mathf::Clamp<float>(view->getCenter().y, mapSize.y - (size.y / 2) * zoom, 0 + (size.y / 2) * zoom));
    }
    center = clampedCenter;

    view->setCenter(center.ToSfVector2());
    window->setView(*this->GetView());
}


void ce::Camera::DoBind(lua_State * L)
{
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Chef")
			.deriveClass<Camera, Component>("Camera")
				.addProperty("size", &Camera::GetSize, &Camera::SetSize)
				.addProperty("center", &Camera::GetCenter, &Camera::SetCenter)
				.addProperty("follow", &Camera::GetFollow, &Camera::SetFollow)
				.addProperty("zoom", &Camera::GetZoom, &Camera::SetZoom)
				.addProperty("view", &Camera::GetView)
			.endClass()
		.endNamespace();
}


