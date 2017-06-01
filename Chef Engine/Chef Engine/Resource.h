#pragma once
#include <string>

namespace ce
{
	class Resource
	{
	public:
		Resource();
		~Resource();

		const std::string GetPath() const;
		virtual void LoadResource(const std::string path);

	protected:
		std::string path;
	};
}
