#pragma once

#include <string>

namespace ce
{
	class Resource
	{
	public:
		virtual void LoadResource(const std::string path);

		const std::string GetPath() const;

	protected:
		std::string path;
	};
}
