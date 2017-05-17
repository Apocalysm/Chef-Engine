#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
#include "MapHandler.h"
#include "Sprite.h"
#include "GameObjectManager.h"
#include "DrawEventManager.h"
#include "Camera.h"

#include <SFML/Graphics.hpp>
#include <Tmx\TmxTile.h>

#include <Windows.h>
#include <typeinfo>
#include <iostream>


/*! \mainpage Main Page
*
*\section intro_sec Introduction
*
* This is an introduction for Chef Engine.
*
*
*\section install_sec How to install Chef Engine
* 
*\subsection step1 Step 1: Do the thing
*\subsection step2 Step 2: Do the other thing
*\subsection step3 Step 3: Now do the first thing and the second thing at the same time.
*
* Now you're finished!
*/
#if _DEBUG
int main(int argc, char* argv[])
#else
int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#endif
{
	// Binds all defined classes with LuaBridge
	//ce::LuaBridgeBinder::BindAll();



	ce::MapHandler* map = new ce::MapHandler;

    ce::GameObjectManager* objManager = new ce::GameObjectManager();
	ce::DrawEventManager* drawManager = new ce::DrawEventManager();

	ce::GameObject* object = new ce::GameObject();

	object->SetName("RandomObject");

	ce::Sprite* sprite = object->AddComponent<ce::Sprite>();
	sprite->SetSprite("Player.png");
	sprite->SetDrawOrder(1);

	ce::Camera* camera = object->AddComponent<ce::Camera>();
	camera->SetSize(sf::Vector2f(69, 420));
	camera->SetFollow(true);

	sf::RenderWindow window(sf::VideoMode(camera->GetSize().x, camera->GetSize().y), "Test");

	window.setFramerateLimit(60);


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
			object->GetTransform()->Move( sf::Vector2f(0, -1));
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			object->GetTransform()->Move( sf::Vector2f(0, 1));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			object->GetTransform()->Move( sf::Vector2f(-1, 0));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			object->GetTransform()->Move( sf::Vector2f(1, 0));
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
		window.setView(camera->GetView());
		window.clear(sf::Color::Cyan);
		drawManager->Draw(window);
		window.display();
	}

	return 0;
}