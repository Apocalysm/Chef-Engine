#include "Resource.h"

using ce::Resource;

const std::string Resource::GetPath() const
{
	return path;
}


void Resource::LoadResource(const std::string path)
{
	this->path = path;
}
