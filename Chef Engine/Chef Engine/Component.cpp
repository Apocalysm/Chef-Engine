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

// MUST FIX THIS SO WE COMPARE HASH_CODE FROM TYPEID
bool Component::operator==(const Component& other)
{
	/*if ()
	{
		return true;
	}*/

	return false;
}
