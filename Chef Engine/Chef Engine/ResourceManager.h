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


#pragma once
#include <map>

namespace ce
{
    class Resource;

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