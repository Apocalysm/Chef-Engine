#include "Object.h"

using ce::Object;

Object::Object()
{
}


Object::~Object()
{
}

Object Object::Instantiate(Object object)
{
	return object;
}

Object Object::Destroy(Object object)
{
	return Object();
}

