#include "Resource.h"

using ce::Resource;

Resource::Resource()
{
}


Resource::~Resource()
{
}


const std::string * Resource::getPath() const
{
	return path;
}


void Resource::loadResource(const std::string * path)
{
	this->path = path;
}
