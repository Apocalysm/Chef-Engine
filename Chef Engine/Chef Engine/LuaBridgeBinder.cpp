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


#include "LuaBridgeBinder.h"

// All the different classes we want to bind with Lua Bridge
#include "GameObject.h"

#include "LuaComponent.h"
#include "Transform.h"
#include "Sprite.h"
#include "Camera.h"
#include "Collider.h"

#include "MapHandler.h"
#include "SFMLKeyboard.h"
#include "SFMLLuaBind.h"

#include "Vec2.h"

#include "LuaBind.h"

// dirent.h Allows us to read directories easier
#include <dirent.h>

#include <iostream>
#include <vector>
#include <string>

using ce::LuaBridgeBinder;

// Creates a templated Bind function
template<typename T>
void ce::LuaBridgeBinder::Bind(lua_State* L)
{
    T::DoBind(L);
}
template<typename T>
void ce::LuaBridgeBinder::Bind(lua_State* L, const std::string& s)
{
    assert(s != "");
    T::DoBind(L, s);
}


// The directory path where we store our .lua-scripts
const std::string LUA_SCRIPTS_PATH = "Lua Scripts";

// The folder that needs to be placed in Lua Scripts to register components
const std::string LUA_COMPONENTS_PATH = "Lua Scripts\\Components";

// The path where the main lua script should be
const std::string MAIN_PATH = "Lua Scripts\\main.lua";

// Values of directory entries representing a directory and a file
const int DIRECTORY_FLAG = (1 << 14);
const int FILE_FLAG = (1 << 15);

// Initializes static variable
int ce::LuaBridgeBinder::componentIDCounter = 0;

// A ref to the main loop in the main script in Lua
std::unique_ptr<luabridge::LuaRef> ce::LuaBridgeBinder::mainFunc;

lua_State* ce::LuaBridgeBinder::L = luaL_newstate();

// Loads a directory and gets all the .lua-files
static const std::vector<std::string*> LoadDirectory(const std::string dir_path)
{
	// A new Dir
	DIR *dir;
	// A new directory entry
	struct dirent *ent;

	// The final vector of string pointers we will return
	std::vector<std::string*> output;

	// First we check if we can open the directory path
	if ((dir = opendir(dir_path.c_str())) != nullptr)
	{
		// Prints all the files and directories within directory
		while ((ent = readdir(dir)) != nullptr)
		{
			// Creates the path for the current directory entry we're checking as a string
			std::string newPath = dir_path;
			newPath.append("\\");
			newPath.append(ent->d_name);
				
			// Checks if the directory entry is a directory
			if (ent->d_type == DIRECTORY_FLAG)
			{	
				// Checks if the directories were either one of the hidden ones, which we skip
				if (std::string(ent->d_name) == "." || std::string(ent->d_name) == "..")
					continue;
				else
				{
					// Recursively calls this method to read the directory on the new path
					const std::vector<std::string*> data = LoadDirectory(newPath);
					
					// Adds the files found in that directory to the complete list of files
					output.insert(output.end(), data.begin(), data.end());
				}
			}
			// Checks if the directory entry is a file
			else if (ent->d_type == FILE_FLAG)
			{
				// Checks if the filename contains .lua
				if (std::string(ent->d_name).find(".lua") != std::string(ent->d_name).npos)
				{
                    // Creates a string for just the name of the file/component which we use later to register it
                    std::string fileName = ent->d_name;
                    // Removes the .lua part
                    fileName.erase(fileName.end() - 4, fileName.end());
                    
                    output.push_back(new std::string(fileName));

					// Adds the name of that file to our vector
					output.push_back(new std::string(newPath));
				}
				else
					continue;
			}
		}
		closedir(dir);

		// Returns all the names of the files we found
		return output;
	}
	else
	{
		// Could not open directory
		perror("Could not open directory");
	}
}

// Call this to call the Bind method in all classes written here
void ce::LuaBridgeBinder::BindAll()
{
	// Create a new lua_State and open default Lua-libraries

	luaL_openlibs(L);

	// Here you put all the method calls for the classes you want to bind
    Bind<ce::GameObject>(L);

    Bind<ce::Component>(L);
    Bind<ce::LuaComponent>(L);
    Bind<ce::Sprite>(L);
    Bind<ce::Transform>(L);
    Bind<ce::Camera>(L);
    Bind<ce::Collider>(L);

    Bind<ce::MapHandler>(L);
    Bind<ce::SFMLKeyboard>(L);
    Bind<ce::SFMLLuaBind>(L);
    Bind<ce::Vec2f>(L, "f");
    Bind<ce::Vec2u>(L, "u");
    Bind<ce::Vec2i>(L, "i");
	
	// Gets all the .lua file_paths
    std::vector<std::string*> file_paths = LoadDirectory(LUA_SCRIPTS_PATH);
	
    //DoRequire(file_paths);

	// Iterates all the file_paths
	for (auto it = file_paths.begin(); it != file_paths.end(); it++)
	{
		// Loads the file using the current file and tablename
		LoadLua(L, (**it), (**(it + 1)));

        it++;
	}
}


// Loads lua file
void ce::LuaBridgeBinder::LoadLua(lua_State * L, const std::string & tableName, const std::string & path)
{

	// Checks if we can load the .lua file or not
	if (luaL_dofile(L, path.c_str()))
	{
		// Writes an error
		std::cerr << lua_tostring(L, -1) << std::endl;
		assert(false);
	}

    // Checks if we placed this file in the Components folder
    if (std::string(path).find(LUA_COMPONENTS_PATH) != std::string(path).npos)
    {
        luabridge::LuaRef table = luabridge::getGlobal(L, tableName.c_str());
        RegisterComponent(table);   
    }
    // Checks if we found our main script
    else if (path == MAIN_PATH)
    {
        luabridge::LuaRef table = luabridge::getGlobal(L, "main");

        // Tries to find the function "main" in Lua
        if (!table["UpdateLoop"].isFunction())
        {
            std::cerr << lua_tostring(table.state(), -1);
            assert(false);
        }
        // Sets the mainFunc ref to the function "main", this will be our main loop
        mainFunc = std::make_unique<luabridge::LuaRef>(table["UpdateLoop"]);
    }
}

// Registers a lua script component's ID
void ce::LuaBridgeBinder::RegisterComponent(luabridge::LuaRef table)
{    
    // Checks if there is an "ID" in the lua script
    if (!table["ID"].isNumber())
    {
        std::cerr << lua_tostring(table.state(), -1);
        assert(false);
    }
    // Registers the ID via our counter that we increment, 
    // thus creating a unique ID for each lua component
    table["ID"] = componentIDCounter++;
}