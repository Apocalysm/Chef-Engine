#pragma once

#include "Resource.h"

#include <map>

namespace ce
{
	class ResourceManager 
	{
	public:
		ResourceManager();
		~ResourceManager();
		
		static Resource* GetResource(const std::string path);
		static void UnloadResource(const std::string path);

	private:
		static std::map<const std::string, Resource*> stringToResource;
	};
}