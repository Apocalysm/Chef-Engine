#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
#include "MapHandler.h"
#include "Sprite.h"
#include "GameObjectManager.h"
#include "DrawEventManager.h"

#include <SFML/Graphics.hpp>
#include <Tmx\TmxTile.h>

#include <Windows.h>
#include <typeinfo>
#include <iostream>

/*! \mainpage My Personal Index
*
*\section intro_sec Introduction
*
* This is the introduction.
*
*\section install_sec Installation
* 
*\subsection step1 Step 1: Do the thing
*\subsection step2 Step 2: Do the other thing
*/
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

    ce::GameObjectManager* objManager = new ce::GameObjectManager();
	ce::DrawEventManager* drawManager = new ce::DrawEventManager();

	ce::GameObject* object = new ce::GameObject();

	ce::Sprite* sprite = object->AddComponent<ce::Sprite>();

	sprite->SetSprite("Hp mana bar.png");
	
	sprite->SetDrawOrder(1);

	map->LoadMap("orthogonal-outside.tmx");

	std::string* mapName = new std::string("orthogonal-outside.tmx");

	map->RegisterMap(0, mapName);

	map->LoadObject();

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
			map->LoadMapIndex(0);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			sprite->SetPosition(sprite->GetPosition() + sf::Vector2f(0, -0.3));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			sprite->SetPosition(sprite->GetPosition() + sf::Vector2f(0, 0.3f));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			sprite->SetPosition(sprite->GetPosition() + sf::Vector2f(-0.3f, 0));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
		    sprite->SetPosition(sprite->GetPosition() + sf::Vector2f(0.3f, 0));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            object->GetTransform()->SetScale(object->GetTransform()->GetScale() + sf::Vector2f(0.001f, 0.001f));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
        {
            object->GetTransform()->SetScale(object->GetTransform()->GetScale() - sf::Vector2f(0.001f, 0.001f));
        }

        objManager->CallUpdate();

		window.clear(sf::Color::Cyan);
		drawManager->Draw(window);
		window.display();


	}

	return 0;
}