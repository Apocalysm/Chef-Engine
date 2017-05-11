#include "Component.h"

#include "GameObject.h"

#include <typeinfo>

int ce::Component::IDCounter = 0;

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


int ce::Component::GetID() const
{
	return ID;
}


void ce::Component::SetID(int ID)
{
	this->ID = ID;
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
	if (this->ID == other.ID)
	{
		return true;
	}

	return false;
}
