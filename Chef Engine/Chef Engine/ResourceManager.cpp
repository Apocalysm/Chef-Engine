#include "ResourceManager.h"

using ce::ResourceManager;

ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}


ce::Resource* ce::ResourceManager::getResource(const std::string * path)
{
	auto resource = stringToResource.find(path);

	if (resource != stringToResource.end())
	{
		return (*resource).second;
	}
	else
	{
		Resource* res = new Resource();
		res->loadResource(path);
		stringToResource[path] = res;
		return res;
	}
}


void ce::ResourceManager::unloadREsource(const std::string * path)
{
	auto resource = stringToResource.find(path);

	if (resource != stringToResource.end())
	{
		delete stringToResource[path];
		stringToResource.erase(resource);
	}
}
