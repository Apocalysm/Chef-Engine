#include "Component.h"
#include "GameObject.h"
#include <typeinfo>


ce::Component::Component()
{
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

int ce::Component::GetHashCode() const
{
	return hash;
}

void ce::Component::SetHashCode(int hash)
{
	this->hash = hash;
}

void ce::Component::SetEnabled(bool enabled)
{
	this->enabled = enabled;
}

bool ce::Component::GetEnabled() const
{
	return enabled;
}

ce::GameObject* ce::Component::GetGameObject() const
{
	return gameObject;
}

void ce::Component::SetGameObject(GameObject * gameObject)
{
	this->gameObject = gameObject;
}

// The == operator of Component compares the hash of the 
bool ce::Component::operator==(const Component& other)
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
