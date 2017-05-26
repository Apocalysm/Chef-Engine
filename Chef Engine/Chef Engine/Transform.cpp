#include "Transform.h"
#include "GameObject.h"
#include "Collider.h"


using ce::Transform;

// Default Constructor
Transform::Transform()
{
	//SetPosition(0, 0);
	position = sf::Vector2f(0.0f, 0.0f);
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


void ce::Transform::Update()
{
	velocity = position - lastPos;
	lastPos = position;
}


// Overload for SetPosition with floats instead of a sf::Vector2f
void Transform::SetPosition(const float x, const float y)
{
	/*if (gameObject->GetComponent<ce::Collider>() != NULL)
	{
		b2Vec2 pos = b2Vec2(x, y);
		gameObject->GetComponent<ce::Collider>()->body->SetTransform(pos, rotation);
	}
	else*/
	SetPosition(sf::Vector2f(x, y));
}


void Transform::SetPosition(const sf::Vector2f& newPosition)
{
	lastPos = position;
	position = newPosition;
}


const sf::Vector2f& Transform::GetPosition() const
{
	return position;
}


void ce::Transform::Move(sf::Vector2f movement)
{
	/*if (gameObject->GetComponent<ce::Collider>() != NULL)
	{
		gameObject->GetComponent<ce::Collider>()->body->ApplyForce(b2Vec2(movement.x, movement.y), gameObject->GetComponent<ce::Collider>()->body->GetWorldCenter(), true);
	}
	else
	{*/
		lastPos = position;
    position += movement;
	//}
}


const sf::Vector2f ce::Transform::GetLastPos() const
{
	return lastPos;
}


const sf::Vector2f ce::Transform::GetVelocity() const
{
	return velocity;
}


void ce::Transform::ResetVelocity()
{
	velocity = sf::Vector2f(0.0f, 0.0f);
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


