#pragma once
#include <string>

namespace ce 
{
	class Object
	{
	public:
		Object();
		~Object();

		std::string name;

		// Specifies what kind of Object this is
		std::string tag;

		// Creates a new instance of the specified Object
		Object Instantiate(Object object);

		// Destroys the specified Object instance
		Object Destroy(Object object);

		int instanceID;
	};
}

