#include "GameObject.h"
#include "Component.h"

//using namespace ce;

// Initializes our ID generator
unsigned long long ce::GameObject::uniqueIDCounter = 0;

ce::GameObject::GameObject()
{
	GameObject("none");
}

ce::GameObject::GameObject(std::string name)
	: Object(name)
{ 
	// Sets the instanceID of the object to the incremented value of uniqueIDCounter
	instanceID = uniqueIDCounter++;

	// The object was instantiated this frame
	isNew = true;
}

void ce::GameObject::SetActive(bool active)
{
	m_active = active;
}


bool ce::GameObject::operator==(const GameObject & other)
{
	if (instanceID == other.instanceID)
	{
		// This is the same gameobject
		return true;
	}

	return false;
}

void ce::GameObject::ComponentUpdate()
{
}
