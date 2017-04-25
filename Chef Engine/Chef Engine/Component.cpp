#include "Component.h"
#include "GameObject.h"
#include <typeinfo>

using ce::Component;

Component::Component()
{
}


Component::~Component()
{
}

void Component::Start()
{

}

void Component::Update()
{

}

int Component::GetHashCode() const
{
	return hash;
}

void Component::SetEnabled(bool enabled)
{
	this->enabled = enabled;
}

bool ce::Component::GetEnabled() const
{
	return enabled;
}
/*
ce::GameObject* Component::GetGameObject() const
{
	//return gameObject;
}*/

// The == operator of Component compares the hash of the 
bool Component::operator==(const Component& other)
{
	if (this->hash == other.hash)
	{
		return true;
	}

	return false;
}
