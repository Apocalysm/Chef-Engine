#include "GameObject.h"

using ce::GameObject;

GameObject::GameObject(std::string name)
{
	name = name;
	instanceID = uniqueIDCounter++;
	isNew = true;
}


// Overloads the '==' operator to compare the instanceID variables of the GameObjects you are comparing
bool ce::GameObject::operator==(const GameObject & other)
{
	if (instanceID == other.instanceID)
	{
		// This is the same GameObjects
		return true;
	}

    // These were not the same GameObjects
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
