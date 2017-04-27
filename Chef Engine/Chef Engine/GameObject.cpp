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

	transform = GetComponent<ce::Transform>();
}

void ce::GameObject::SetActive(bool active)
{
	m_active = active;
}

bool ce::GameObject::GetActive()
{
	return m_active;
}

void ce::GameObject::SetLayer(Layers newLayer)
{
}

int ce::GameObject::GetLayer()
{
	return layer;
}

void ce::GameObject::SetTransform(ce::Transform* transform)
{
	this->transform = transform;
}

ce::Transform* ce::GameObject::GetTransform() const
{
	return transform;
}

unsigned long long ce::GameObject::GetID()
{
	return instanceID;
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
