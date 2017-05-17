#include "Component.h"

#include "GameObject.h"

#include <typeinfo>


ce::Component::Component()
{
    isNew = true;
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

void ce::Component::SetIsNew(bool isNew)
{
    this->isNew = isNew;
}

bool ce::Component::GetIsNew() const
{
    return isNew;
}


ce::GameObject* ce::Component::GetGameObject() const
{
	return gameObject;
}


void ce::Component::SetGameObject(GameObject * gameObject)
{
	this->gameObject = gameObject;
}


// The == operator of Component compares the ID of the component
bool ce::Component::operator==(const Component& other)
{
	if (this->ID == other.ID)
	{
		return true;
	}

	return false;
}
