#include "ResourceManager.h"
#include "Texture.h"
#include "SoundBuffer.h"

std::map<const std::string, ce::Resource*> ce::ResourceManager::stringToResource;

using ce::ResourceManager;

ce::Resource* ce::ResourceManager::GetResource(const std::string path)
{
	// Gets resource with the path passed in this method
	auto resource = stringToResource.find(path);

	// If the resource was found
	if (resource != stringToResource.end())
	{
		return (*resource).second;
	}
	else
	{
		Resource* res;

		// If the requested resource is an image
		if (path.find(".png") || path.find(".jpg") || path.find(".bmp") || path.find(".gif") || path.find(".tga") || path.find(".psd") || path.find(".hdr") || path.find(".pic"))
		{
			// Creates resource as a Texture
			res = new ce::Texture();
		}
		// If the requested resource is a sound
		else if (path.find(".wav") || path.find(".ogg") || path.find(".flac") || path.find(".raw") || path.find(".aiff"))
		{
			// Creates resource as a SoundBuffer
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
	// Gets requseted resource
	auto resource = stringToResource.find(path);

	// If resource was found
	if (resource != stringToResource.end())
	{
		// Deletes and erases resource from the map
		delete stringToResource[path];
		stringToResource.erase(resource);
	}
}
