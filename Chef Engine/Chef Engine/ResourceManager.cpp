#include "ResourceManager.h"
#include "Texture.h"
#include "SoundBuffer.h"

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

		std::size_t strPos = path.find(".");
		std::string fileType = path.substr(strPos);

		if (fileType == ".png" || fileType == ".jpg" || fileType == ".bmp" || fileType == ".gif" || fileType == ".tga" || fileType == ".psd" || fileType == ".hdr" || fileType == ".pic")
		{
			res = new ce::Texture();
		}
		else if (fileType == ".wav" || fileType == ".ogg" || fileType == ".flac" || fileType == ".raw" || fileType == ".aiff")
		{
			res = new ce::SoundBuffer();
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
