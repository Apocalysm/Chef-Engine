#include "Object.h"

using ce::Object;

Object::Object()
{
	name = "none";
}

Object::Object(std::string name)
{
	this->name = name;
}


Object::~Object()
{
}

// Getter and setter methods for 'name' variable
std::string ce::Object::GetName() const
{
	return name;
}
void ce::Object::SetName(std::string name)
{
	this->name = name;
}

// Getter and setter methods for 'tag' variable
std::string ce::Object::GetTag() const
{
	return tag;
}
void ce::Object::SetTag(std::string tag)
{
	this->tag = tag;
}


Object Object::Instantiate(Object object)
{
	return object;
}

Object Object::Destroy(Object object)
{
	return Object();
}

void ce::Object::DoBind(lua_State * L)
{
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Chef")
			.beginClass<Object>("Object")
				.addConstructor<void(*)(void)>()
				.addProperty("name", &Object::GetName, &Object::SetName)
				.addProperty("tag", &Object::GetTag, &Object::SetTag)
				.addFunction("Instantiate", &Object::Instantiate)
				.addFunction("Destroy", &Object::Destroy)
			.endClass()
		.endNamespace();
}

