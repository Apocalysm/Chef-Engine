#include "SFMLKeyboard.h"

using ce::SFMLKeyboard;

bool* ce::SFMLKeyboard::keys = 0;

SFMLKeyboard::SFMLKeyboard()
{
}


SFMLKeyboard::~SFMLKeyboard()
{
}

void ce::SFMLKeyboard::Initialize()
{
	keys = new bool[sf::Keyboard::KeyCount];
	for (auto i = 0; i < sf::Keyboard::KeyCount; i++)
	{
		keys[i] = false;
	}
}

bool ce::SFMLKeyboard::GetKey(sf::Keyboard::Key key)
{
	return keys[key];
}

bool ce::SFMLKeyboard::GetKeyDown(sf::Keyboard::Key key)
{
	return false;
}

bool ce::SFMLKeyboard::GetKeyUp(sf::Keyboard::Key key)
{
	return false;
}
