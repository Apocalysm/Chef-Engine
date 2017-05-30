#include "ResourceManager.h"
#include "Texture.h"
#include "SoundBuffer.h"
#include "Font.h"

#include <assert.h>

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

		std::size_t strPos = path.find(".");
		std::string fileType = path.substr(strPos);

		if (fileType == ".png" || fileType == ".jpg" || fileType == ".bmp" || fileType == ".gif" || fileType == ".tga" || fileType == ".psd" || fileType == ".hdr" || fileType == ".pic")
		{
			// Creates resource as a Texture
			res = new ce::Texture();
		}
		else if (fileType == ".wav" || fileType == ".ogg" || fileType == ".flac" || fileType == ".raw" || fileType == ".aiff")
		{
			// Creates resource as a SoundBuffer
			res = new ce::SoundBuffer();
		}
		// If the requested resource is a font
		else if (fileType == ".fnt" || fileType == ".ttf" || fileType == ".lwfn" || fileType == ".cff" || fileType == ".otf" || fileType == ".sfnt" || fileType == ".bdf" || fileType == ".pfr")
		{
			// Creates resource as Font
			res = new ce::Font();
		}
		else
		{
			assert(!"Unsupported file format!");

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
