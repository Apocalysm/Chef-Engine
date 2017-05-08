#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
#include "MapHandler.h"
#include "Sprite.h"
#include "GameObjectManager.h"
#include "DrawEventManager.h"

#include <Windows.h>
#include <typeinfo>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <Tmx\TmxTile.h>

#if _DEBUG
int main(int argc, char* argv[])
#else
int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#endif
{
	// Binds all defined classes with LuaBridge
	LuaBridgeBinder::BindAll();

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Test");

	ce::MapHandler* map = new ce::MapHandler;

	ce::DrawEventManager* drawManager = new ce::DrawEventManager();

	map->LoadMap("orthogonal-outside.tmx");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		window.clear(sf::Color::Cyan);

		drawManager->Draw(window);
		window.display();


	}

	return 0;
}