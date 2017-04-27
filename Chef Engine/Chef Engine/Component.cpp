#include "Component.h"
#include "GameObject.h"
#include <typeinfo>

using ce::Component;

Component::Component()
{
}


Component::~Component()
{
}

void Component::Start()
{

}

void Component::Update()
{

}

int Component::GetHashCode() const
{
	return hash;
}

void ce::Component::SetHashCode(int hash)
{
	this->hash = hash;
}

void Component::SetEnabled(bool enabled)
{
	this->enabled = enabled;
}

bool ce::Component::GetEnabled() const
{
	return enabled;
}

GameObject* Component::GetGameObject() const
{
	return gameObject;
}

// The == operator of Component compares the hash of the 
bool Component::operator==(const Component& other)
{
	if (this->hash == other.hash)
	{
		return true;
	}

	return false;
}

void ce::Component::DoBind(lua_State * L)
{
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Chef")
			.beginClass<Component>("Component")
				.addProperty("hash_code", &Component::GetHashCode)
				.addProperty("enabled", &Component::GetEnabled, &Component::SetEnabled)
				.addProperty("gameObject", &Component::GetGameObject)
				.addFunction("Equals", &Component::operator==)
			.endClass()
		.endNamespace();
}
