#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
#include "MapHandler.h"
#include "Sprite.h"
#include "GameObjectManager.h"
#include "DrawEventManager.h"
#include "Collider.h"

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

	sprite->SetSprite("image.jpg");
	
	sprite->SetDrawOrder(1);

	//sprite->SetOrigin(200.0f, 100.0f);
	object->GetTransform()->SetScale(3.0f, 3.0f);

	object->GetTransform()->SetPosition(200.0f, 200.0f);

	ce::Collider* collBox = object->AddComponent<ce::Collider>();

	collBox->FitSprite();


	/*b2Vec2 gravity(0.0f, 0.0f);
	b2World world(gravity);
	b2BodyDef bodyDef;
	bodyDef.position.Set(100.0f, 100.0f);
	b2Body* body = world.CreateBody(&bodyDef);*/

	sf::CircleShape shape(50);



	//map->LoadMap("sewers.tmx");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			map->LoadMap("sewers.tmx");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			map->LoadMap("orthogonal-outside.tmx");
		}*/

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			object->GetTransform()->SetPosition(object->GetTransform()->GetPosition() + sf::Vector2f(0, -0.3));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			object->GetTransform()->SetPosition(object->GetTransform()->GetPosition() + sf::Vector2f(0, 0.3f));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			object->GetTransform()->SetPosition(object->GetTransform()->GetPosition() + sf::Vector2f(-0.3f, 0));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			object->GetTransform()->SetPosition(object->GetTransform()->GetPosition() + sf::Vector2f(0.3f, 0));
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