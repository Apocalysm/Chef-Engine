#pragma once
#include "Resource.h"
#include <string>

namespace sf
{
    class Texture;
}

namespace ce
{
	class Texture : public Resource
	{
	public:
		Texture();
		~Texture();

		// Sets the 'path' variable and loads the file
		void LoadResource(const std::string path);

		sf::Texture* GetTexture() const;

	private:
		sf::Texture* texture;
	};
}