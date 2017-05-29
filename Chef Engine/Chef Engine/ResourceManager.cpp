#include "ResourceManager.h"
#include "Texture.h"
#include "SoudBuffer.h"

std::map<const std::string, ce::Resource*> ce::ResourceManager::stringToResource;

using ce::ResourceManager;

ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}


ce::Resource* ce::ResourceManager::GetResource(const std::string path)
{
	auto resource = stringToResource.find(path);

	if (resource != stringToResource.end())
	{
		return (*resource).second;
	}
	else
	{
		Resource* res;

		if (path.find(".png") || path.find(".jpg") || path.find(".bmp") || path.find(".gif") || path.find(".tga") || path.find(".psd") || path.find(".hdr") || path.find(".pic"))
		{
			res = new ce::Texture();
		}
		else if (path.find(".wav") || path.find(".ogg") || path.find(".flac") || path.find(".raw") || path.find(".aiff"))
		{
			res = new ce::SoudBuffer();
		}
		else
		{
			res = new Resource();
		}

		res->LoadResource(path);
		stringToResource[path] = res;
		return res;
	}
}


void ce::ResourceManager::UnloadResource(const std::string path)
{
	auto resource = stringToResource.find(path);

	if (resource != stringToResource.end())
	{
		delete stringToResource[path];
		stringToResource.erase(resource);
	}
}
