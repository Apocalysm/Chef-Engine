#pragma once

#include <SFML\Graphics.hpp>

namespace ce
{
	class SFMLKeyboard
	{
	public:
		SFMLKeyboard();
		~SFMLKeyboard();

		void Initialize();
		bool GetKey(sf::Keyboard::Key key);
		bool GetKeyDown(sf::Keyboard::Key key);
		bool GetKeyUp(sf::Keyboard::Key key);
		
	private:
		static bool* keys;
	};
}

