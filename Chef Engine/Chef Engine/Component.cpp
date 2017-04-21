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

bool Component::operator==(const Component& other)
{
	/*if (typeid(other).hash_code() == typeid(this).hash_code())
	{
		return true;
	}*/

	return false;
}