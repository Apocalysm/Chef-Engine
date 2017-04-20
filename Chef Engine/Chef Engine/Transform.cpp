#include "Transform.h"



ce::Transform::Transform()
{
}


ce::Transform::~Transform()
{
}

void ce::Transform::SetRotation(float newRotation)
{
	rotation = newRotation;
}

void ce::Transform::SetPosition(const sf::Vector2f& newPosition)
{
	position = newPosition;
}

void ce::Transform::SetScale(const sf::Vector2f& newScale)
{
	scale = newScale;
}

void ce::Transform::Rotate(float angle)
{
	rotation += angle;
}
