#pragma once

#include <string>

namespace ce
{
	class Resource
	{
	public:
		Resource();
		~Resource();

		const std::string* getPath() const;
		void loadResource(const std::string* path);

	protected:
		const std::string* path;
	};
}
