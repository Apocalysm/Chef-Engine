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


#include "ResourceManager.h"

#include "Resource.h"
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

		if (path.find(".png") || path.find(".jpg") || path.find(".bmp") || path.find(".gif") || path.find(".tga") || path.find(".psd") || path.find(".hdr") || path.find(".pic"))
		{
			res = new ce::Texture();
		}
		else if (path.find(".wav") || path.find(".ogg") || path.find(".flac") || path.find(".raw") || path.find(".aiff"))
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
