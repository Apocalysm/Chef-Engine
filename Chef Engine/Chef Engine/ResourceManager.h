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
		
		Resource* getResource(const std::string* path);
		void unloadREsource(const std::string* path);

	private:
		std::map<const std::string*, Resource*> stringToResource;
	};
}