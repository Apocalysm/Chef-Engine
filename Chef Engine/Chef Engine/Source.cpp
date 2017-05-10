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
	ce::LuaBridgeBinder::BindAll();

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Test");

	ce::MapHandler* map = new ce::MapHandler;

	ce::DrawEventManager* drawManager = new ce::DrawEventManager();

	ce::GameObject* object = new ce::GameObject();

	ce::Sprite* sprite = object->AddComponent<ce::Sprite>();

	sprite->SetSprite("Hp mana bar.png");
	
	sprite->SetDrawOrder(1);

	map->LoadMap("orthogonal-outside.tmx");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			map->LoadMap("sewers.tmx");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			map->LoadMap("orthogonal-outside.tmx");
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			sprite->SetPosition(sprite->GetPosition() + sf::Vector2f(0, -1));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			sprite->SetPosition(sprite->GetPosition() + sf::Vector2f(0, 0.3));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			sprite->SetPosition(sprite->GetPosition() + sf::Vector2f(-0.3, 0));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
			sprite->SetPosition(sprite->GetPosition() + sf::Vector2f(0.3, 0));
			}

		window.clear(sf::Color::Cyan);

		drawManager->Draw(window);
		window.display();


	}

	return 0;
}