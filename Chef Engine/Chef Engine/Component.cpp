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

// The == operator of Component compares the hash of the 
bool Component::operator==(const Component& other)
{
	if (this->hash == other.hash)
	{
		return true;
	}

	return false;
}
