#pragma once
#include "LuaBridgeBinder.h"
#include <string>

namespace ce 
{
	class Object
	{
		// Befriends the templated Bind function so it can access our protected functions
		friend void LuaBridgeBinder::Bind<ce::Object>(lua_State*);

	public:
		Object();
		Object(std::string name);
		~Object();

		// Getter and setter methods for 'name' variable
		std::string GetName();
		void SetName(std::string name);

		// Getter and setter methods for 'tag' variable
		std::string GetTag();
		void SetTag(std::string tag);

		// Creates a new instance of the specified Object
		Object Instantiate(Object object);

		// Destroys the specified Object instance
		Object Destroy(Object object);

	protected:
		static void DoBind(lua_State* L);

	private:
		std::string name;

		// Specifies what kind of Object this is
		std::string tag;
	};
}

