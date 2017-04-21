#include "GameObject.h"
#include "Component.h"

using ce::GameObject;

GameObject::GameObject(std::string name)
{
	name = name;
	instanceID = uniqueIDCounter++;
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
	for (auto it = components.begin(); it != components.end(); it++)
	{
		(*it)->Update();
	}
}

template<typename T>
T GameObject::GetComponent(T)
{
	return T();
}

template<typename T>
T ce::GameObject::AddComponent(T)
{
	return T();
}

template<typename T>
void GameObject::RemoveComponent(T)
{
}
