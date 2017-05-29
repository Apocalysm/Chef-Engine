#include "Camera.h"
#include "GameObject.h"
#include "MapHandler.h"
#include "Math.h"

using ce::Camera;

Camera* Camera::main;
sf::RenderWindow* Camera::window;

Camera::Camera()
    : zoom(1), follow(false), step(1)
{
    if (main == nullptr)
    {
        main = this;
        window->setView(this->GetView());
    }
}


Camera::~Camera()
{
}


void ce::Camera::SetSize(const sf::Vector2f &size)
{
	this->size = size;
	view.setSize(size);
}


sf::Vector2f ce::Camera::GetSize() const
{
	return size;
}


void ce::Camera::SetZoom(float zoom)
{
	view.zoom(zoom);
	this->zoom *= zoom;
}


float ce::Camera::GetZoom() const
{
	return this->zoom;
}

void ce::Camera::SetStep(float step)
{
    this->step = step;
}

float ce::Camera::GetStep() const
{
    return this->step;
}


sf::View ce::Camera::GetView() const
{
	return this->view;
}


void ce::Camera::SetCenter(const sf::Vector2f &center)
{
	this->center = center;
	view.setCenter(center);
}


sf::Vector2f ce::Camera::GetCenter() const
{
	return this->center;
}


bool ce::Camera::GetFollow() const
{
	return this->follow;
}


void ce::Camera::SetFollow(const bool & follow)
{
	this->follow = follow;
}


void ce::Camera::UpdateCamera()
{
    if (follow)
    {
        center = sf::Vector2f(ce::Math::Lerp(center.x, gameObject->GetTransform()->GetPosition().x, step),
                              ce::Math::Lerp(center.y, gameObject->GetTransform()->GetPosition().y, step));
        view.setCenter(center);
    }

    mapSize = ce::MapHandler::GetMapSize();

    sf::Vector2f clampedCenter = center;
    
    if (mapSize.x > 0 && mapSize.y > 0)
    {
        clampedCenter = sf::Vector2f(ce::Math::ClampF(view.getCenter().x, mapSize.x - (size.x / 2) * zoom, 0 + (size.x / 2) * zoom),
        ce::Math::ClampF(view.getCenter().y, mapSize.y - (size.y / 2) * zoom, 0 + (size.y / 2) * zoom));
    }
    center = clampedCenter;

    view.setCenter(center);
    window->setView(this->GetView());
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
                .addProperty("step", &Camera::GetStep, &Camera::SetStep)
			.endClass()
		.endNamespace();
}
