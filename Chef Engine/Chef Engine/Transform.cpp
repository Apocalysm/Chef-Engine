#include "Transform.h"


using ce::Transform;

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

void ce::Transform::Start()
{
}



void Transform::SetPosition(const float x, const float y)
{
	SetPosition(sf::Vector2f(x, y));
}

const sf::Vector2f & ce::Transform::GetPosition() const
{
	return position;
}

void Transform::SetPosition(const sf::Vector2f& newPosition)
{
	position = newPosition;
}


void Transform::SetRotation(float newRotation)
{
	rotation = newRotation;
}
void Transform::Rotate(float angle)
{
	rotation += angle;
}


void Transform::SetScale(const float x, const float y)
{
	SetScale(sf::Vector2f(x, y));
}

void Transform::SetScale(const sf::Vector2f& newScale)
{
	scale = newScale;
}


