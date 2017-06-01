#pragma once
#include <string>

namespace ce
{
	class Resource
	{
	public:
		virtual void LoadResource(const std::string path);

		const std::string GetPath() const;

		void IncrementUseCount();

		void DecrementUseCount();

		int GetUseCount() const;

	protected:
		std::string path;

		// The amount of objects using this resource
		int useCount;
	};
}
