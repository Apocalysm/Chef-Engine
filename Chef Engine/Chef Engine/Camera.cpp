#include "Camera.h"
#include "GameObject.h"

using ce::Camera;

Camera::Camera()
{
	follow = false;
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


sf::View ce::Camera::GetView() const
{
	return view;
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


void ce::Camera::Move(const sf::Vector2f &offset)
{
	view.move(offset);
}

bool ce::Camera::GetFollow() const
{
	return follow;
}

void ce::Camera::SetFollow(const bool & follow)
{
	this->follow = follow;
}


void ce::Camera::Update()
{
	if (follow)
	{
		view.setCenter(gameObject->GetTransform()->GetPosition());
	}
}


