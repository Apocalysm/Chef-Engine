#pragma once

#include "Resource.h"

#include <map>

namespace ce
{
	class ResourceManager 
	{
	public:
		// Returns requested resource with passed path
		static Resource* GetResource(const std::string path);

		// Checks if resources are being used, deletes them if not
		static void Update();

		// Removes requested resource with passed path
		static void UnloadResource(const std::string path);

	private:
		// Contains Resources assigned to their paths as keys
		static std::map<const std::string, Resource*> stringToResource;
	};
}