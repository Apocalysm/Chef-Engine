#include "GameObject.h"

using ce::GameObject;

GameObject::GameObject(std::string name)
{
	name = name;
}


GameObject::~GameObject()
{
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
