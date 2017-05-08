#include "Transform.h"


using ce::Transform;

// Default Constructor
Transform::Transform()
{
	SetPosition(0, 0);
	SetRotation(0);
	SetScale(1, 1);
}

Transform::Transform(const sf::Vector2f& position, const float rotation, const sf::Vector2f& scale)
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

// Overload for SetPosition with floats instead of a sf::Vector2f
void Transform::SetPosition(const float x, const float y)
{
	SetPosition(sf::Vector2f(x, y));
}
void Transform::SetPosition(const sf::Vector2f& newPosition)
{
	position = newPosition;
}

const sf::Vector2f& Transform::GetPosition() const
{
	return position;
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
	SetScale(sf::Vector2f(x, y));
}

sf::Vector2f ce::Transform::GetScale() const
{
	return scale;
}

void Transform::SetScale(const sf::Vector2f& newScale)
{
	scale = newScale;
}


