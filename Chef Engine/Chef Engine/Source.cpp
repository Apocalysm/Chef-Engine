#include "Component.h"
#include "GameObject.h"
#include "Transform.h"

#include <Windows.h>
#include <typeinfo>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <Tmx\TmxTile.h>

// Initializes our ID generator
unsigned long long ce::GameObject::uniqueIDCounter = 0;

#if _DEBUG
int main()
#else
int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#endif
{	
	ce::GameObject obj("hej");

	for (size_t i = 0; i < 10; i++)
		ce::Transform* transform = obj.AddComponent<ce::Transform>();
	

	sf::RenderWindow window(sf::VideoMode(200, 200), "Test");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			obj.AddComponent<ce::Transform>();
			std::cout << obj.GetComponent<ce::Transform>()->hash << std::endl;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
			obj.RemoveComponent<ce::Transform>();

		window.clear();

		window.display();
	}

	return 0;
}