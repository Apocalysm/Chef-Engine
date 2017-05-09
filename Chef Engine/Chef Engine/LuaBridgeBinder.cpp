#include "LuaBridgeBinder.h"

// All the different classes we want to bind with Lua Bridge
#include "Object.h"
#include "Component.h"
#include "LuaComponent.h"

#include <iostream>
#include <vector>

// Allows us to read directories easier
#include <dirent.h>

// Linking a library through code
#pragma comment(lib, "lua53.lib")

using ce::LuaBridgeBinder;

// Creates a templated Bind function
template<typename T>
void LuaBridgeBinder::Bind(lua_State* L)
{
	T::DoBind(L);
}

// The directory path where we store our .lua-scripts
const std::string LUA_SCRIPTS_PATH = "Lua Scripts";

// Values of directory entries representing a directory and a file
const int DIRECTORY_FLAG = (1 << 14);
const int FILE_FLAG = (1 << 15);

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
                    // Creates a string for just the name of the file which will be used in DoRequire() later
                    output.push_back(new std::string(ent->d_name));

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
void LuaBridgeBinder::BindAll()
{
	// Create a new lua_State and open default Lua-libraries
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);


	// Here you put all the method calls for the classes you want to bind
	Bind<ce::Component>(L);

	
	// Gets all the .lua file_paths
    std::vector<std::string*> file_paths = LoadDirectory(LUA_SCRIPTS_PATH);
	
    //DoRequire(file_paths);

	// Iterates all the file_paths
	for (auto it = file_paths.begin(); it != file_paths.end(); it++)
	{
        it++;
		// Loads the file using the current iteration of file_path
		LoadLua(L, (**it));
	}
}

// Loads lua file
void LuaBridgeBinder::LoadLua(lua_State * L, const std::string & path)
{
	// Checks if we can load the .lua file or not
	if (luaL_dofile(L, path.c_str()))
	{
		// Writes an error
		std::cerr << lua_tostring(L, -1) << std::endl;
		assert(false);
	}
}