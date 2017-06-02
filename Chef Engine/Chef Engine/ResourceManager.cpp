////////////////////////////////////////////////////////////
//
// Chef Engine
// Copyright (C) 2017 Oskar Svensson
//  
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//
// Author: Dennis Karlsson
//
////////////////////////////////////////////////////////////


#include "ResourceManager.h"

#include "Resource.h"
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
		(*resource).second->IncrementUseCount();
		return (*resource).second;
	}
	else
	{
		Resource* res;

		std::size_t strPos = path.find(".");
		std::string fileType = path.substr(strPos);

		// If the requested resource is an image
		if (fileType == ".png" || fileType == ".jpg" || fileType == ".bmp" || fileType == ".gif" || fileType == ".tga" || fileType == ".psd" || fileType == ".hdr" || fileType == ".pic")
		{
			// Creates resource as a Texture
			res = new ce::Texture();
		}
		// If the requested resource is a sound
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

		res->IncrementUseCount();

		res->LoadResource(path);

		stringToResource[path] = res;

		return res;
	}
}


void ce::ResourceManager::Update()
{
	// If there are any resources
	if (stringToResource.size() != 0)
	{
		for (auto it = stringToResource.begin(); it != stringToResource.end();)
		{
			// If the resource isn't being used
			if (it->second->GetUseCount() == 0)
			{
				// Deletes and erases the resource
				delete it->second;
				it = stringToResource.erase(it);
			}
			else
			{
				it++;
			}
		}
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
