#include "LuaBridgeBinder.h"

#include <fstream>

// All the different classes we want to bind with Lua Bridge
#include "Object.h"
#include "Component.h"

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

void LuaBridgeBinder::DoRequire(const std::vector<std::string*> & paths)
{
    std::fstream lua_file;

    std::vector<std::string*> fileNames;
    for (auto it = paths.begin(); it != paths.end(); it += 2)
    {
        std::string* newFileName = new std::string();
        *newFileName = (**it);
        newFileName->erase(newFileName->length() - 4, 4);
        fileNames.push_back(newFileName);
    }

    std::vector<std::string*> filePaths;
    for (auto it = paths.begin(); it != paths.end(); it++)
    {
        it++;
        std::string* newFilePath = new std::string();
        *newFilePath = (**it);
        newFilePath->erase(newFilePath->length() - (*(it -1))->length(), (*(it - 1))->length());

        std::vector<int> characterLocations;
        for (int i = 0; i < newFilePath->length(); i++)
        {
            if ((*newFilePath)[i] == '\\')
                characterLocations.push_back(i);
        }

        for (auto inner_it = characterLocations.begin(); inner_it != characterLocations.end(); inner_it++)
        {
            (*newFilePath)[*inner_it] = '/';
        }

        filePaths.push_back(newFilePath);
    }

    for (auto outer_it = paths.begin(); outer_it != paths.end(); outer_it++)
    {
        outer_it++;  

        std::stringstream file_dump;

        file_dump << "package.path = package.path .. \"";

        for (auto inner_it = filePaths.begin(); inner_it != filePaths.end(); inner_it++)
        {
            if (inner_it > filePaths.begin())
            {
                if(**inner_it != (**(inner_it - 1)))
                    file_dump << ";../Chef Engine/" << (**inner_it) << "?.lua";
            }
            else
                file_dump << ";../Chef Engine/" << (**inner_it) << "?.lua";
        }

        file_dump << "\"" << std::endl;

        for (auto inner_it = fileNames.begin(); inner_it != fileNames.end(); inner_it++)
        {
            if ((*outer_it)->find(**inner_it) == (*outer_it)->npos)
            {
                file_dump << "require \"" << (**inner_it) << "\"" << std::endl;
            }
        }

        lua_file.open((*outer_it)->c_str());
        
        std::string str;

        while (std::getline(lua_file, str))
        {
            file_dump << str << std::endl;
        }

        lua_file.close();

        lua_file.open((*outer_it)->c_str(), std::fstream::out | std::fstream::trunc);

        lua_file << file_dump.str();

        lua_file.close();
    }
}
