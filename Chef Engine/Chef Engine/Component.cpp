#include "Component.h"

#include "GameObject.h"

#include <typeinfo>


ce::Component::Component()
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


int ce::Component::GetHashCode() const
{
	return hash;
}


void ce::Component::SetHashCode(int hash)
{
	this->hash = hash;
}


void ce::Component::SetEnabled(bool enabled)
{
	this->enabled = enabled;
}


bool ce::Component::GetEnabled() const
{
	return enabled;
}


ce::GameObject* ce::Component::GetGameObject() const
{
	return gameObject;
}


void ce::Component::SetGameObject(GameObject * gameObject)
{
	this->gameObject = gameObject;
}


// The == operator of Component compares the hash of the component
bool ce::Component::operator==(const Component& other)
{
	if (this->hash == other.hash)
	{
		return true;
	}

	return false;
}
