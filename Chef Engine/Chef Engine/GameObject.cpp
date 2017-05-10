#include "GameObject.h"

#include "Component.h"
#include "Sprite.h"
#include "GameObjectManager.h"
#include "DrawEventManager.h"


using ce::GameObject;

const int GameObject::LAYER_AMOUNT = 6;

// Initializes our ID generator
unsigned long long GameObject::uniqueIDCounter = 0;

GameObject::GameObject()
	: GameObject("none")
{
}


GameObject::GameObject(std::string name)
{ 
	// Sets the instanceID of the object to the incremented value of uniqueIDCounter
	instanceID = uniqueIDCounter++;

	// The object was instantiated this frame
	isNew = true;

	transform = AddComponent<ce::Transform>();

	ce::GameObjectManager::AddObject(this);

    m_active = true;

    layer = Default;
}


GameObject::~GameObject()
{
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


bool ce::GameObject::operator==(const GameObject & other)
{
	if (instanceID == other.instanceID)
	{
		// This is the same gameobject
		return true;
	}
	return false;
}


void GameObject::ComponentUpdate()
{
	for (auto it = components.begin(); it != components.end(); it++)
	{
		it->second->Update();
	}
}


// Adds a new component of the specified type
ce::Component* GameObject::AddComponent(const int hash)
{
    if (GameObject::GetComponentInternal(hash) == nullptr)
    {
        return nullptr;
    }

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


// Getter and setter methods for 'name' variable
std::string GameObject::GetName() const
{
	return name;
}


void GameObject::SetName(std::string name)
{
	this->name = name;
}


// Getter and setter methods for 'tag' variable
std::string GameObject::GetTag() const
{
	return tag;
}


void GameObject::SetTag(std::string tag)
{
	this->tag = tag;
}


void GameObject::Destroy()
{
	ce::Sprite* spr = GetComponentInternal<ce::Sprite>();

	if (spr != nullptr)
	{
		ce::DrawEventManager::RemoveSprite(spr);
		//delete GetComponent<Sprite>()->;
	}

	// Iterates all of GameObject's components
	for (auto it = components.begin(); it != components.end(); it++)
	{
		// Deletes the component from the vector and the memory
        delete it->second;
	}
    components.clear();

	ce::GameObjectManager::RemoveObject(this);
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
			.endClass()
		.endNamespace();
}

