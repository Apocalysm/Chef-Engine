#include "GameObject.h"

using ce::GameObject;

GameObject::GameObject(std::string name)
{
	name = name;
	instanceID = uniqueIDCounter++;
	isNew = true;
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
