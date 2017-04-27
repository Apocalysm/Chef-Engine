#include "GameObject.h"
#include "Component.h"

using ce::GameObject;

// Initializes our ID generator
unsigned long long ce::GameObject::uniqueIDCounter = 0;

GameObject::GameObject()
{
	GameObject("none");
}

GameObject::GameObject(std::string name)
	: Object(name)
{ 
	// Sets the instanceID of the object to the incremented value of uniqueIDCounter
	instanceID = uniqueIDCounter++;

	// The object was instantiated this frame
	isNew = true;

	transform = GetComponentInternal<ce::Transform>();
}

void GameObject::SetActive(bool active)
{
	m_active = active;
}

bool GameObject::GetActive() const
{
	return m_active;
}

void GameObject::SetLayer(Layers newLayer)
{
}

int GameObject::GetLayer() const
{
	return layer;
}

void GameObject::SetTransform(ce::Transform* transform)
{
	this->transform = transform;
}

ce::Transform* GameObject::GetTransform() const
{
	return transform;
}

unsigned long long GameObject::GetID() const
{
	return instanceID;
}

void GameObject::ComponentUpdate()
{
	for (auto it = components.begin(); it != components.end(); it++)
	{
		(*it).second->Update();
	}
}

// Adds a new component of the specified type
ce::Component* GameObject::AddComponent(const int hash)
{
	if(GameObject::GetComponentInternal(hash) == nullptr)
		return nullptr;
		
}

// Tries to get a component of the specified type from GameObject's vector 'components'
ce::Component* GameObject::GetComponentInternal(const int hash)
{
	Component* comp = components[hash];

	return comp;
}

// Uses GetComponentInternal and also writes an error message to the console if we couldn't find anything
ce::Component* GameObject::GetComponent(const int hash)
{
	Component* comp = GetComponentInternal(hash);

	if (comp == nullptr)
	{
		std::cerr << "Could not find component" << std::endl;

		return nullptr;
	}

	return comp;
}

void GameObject::RemoveComponent(const int hash)
{
	// delete the object from the vector and the memory
	delete components[hash];
}

bool GameObject::operator==(const GameObject& other)
{
	if (this->layer == other.GetLayer())
	{
		if (this->instanceID == other.GetID())
			return true;
	}

	return false;
}

void GameObject::DoBind(lua_State * L)
{
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Chef")
			.beginClass<GameObject>("GameObject")
				.addProperty("active", &GameObject::GetActive, &GameObject::SetActive)
				.addProperty("layer", &GameObject::GetLayer, &GameObject::SetLayer)
				.addProperty("instanceID", &GameObject::GetID)
				.addFunction("AddComponent", &GameObject::AddComponent)
				.addFunction("GetComponent", &GameObject::GetComponent)
				.addFunction("RemoveComponent", &GameObject::RemoveComponent)
				.addFunction("Equals", &GameObject::operator==)
			.endClass()
		.endNamespace();
			

}

