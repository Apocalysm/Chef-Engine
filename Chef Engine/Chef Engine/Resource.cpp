#include "Resource.h"

using ce::Resource;

const std::string Resource::GetPath() const
{
	return path;
}


void ce::Resource::IncrementUseCount()
{
	useCount++;
}


void ce::Resource::DecrementUseCount()
{
	useCount--;
}


int ce::Resource::GetUseCount() const
{
	return useCount;
}


void Resource::LoadResource(const std::string path)
{
	this->path = path;
}
