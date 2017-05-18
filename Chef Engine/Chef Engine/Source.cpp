#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
#include "MapHandler.h"
#include "Sprite.h"
#include "GameObjectManager.h"
#include "DrawEventManager.h"
#include "Collider.h"
#include "CollisionManager.h"

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
	window.setFramerateLimit(60);

	ce::MapHandler* map = new ce::MapHandler;

    ce::GameObjectManager* objManager = new ce::GameObjectManager();
	ce::DrawEventManager* drawManager = new ce::DrawEventManager();
	ce::CollisionManager* collManager = new ce::CollisionManager();

	ce::GameObject* object = new ce::GameObject();

	ce::Sprite* sprite = object->AddComponent<ce::Sprite>();

	sprite->SetSprite("image.jpg");
	
	sprite->SetDrawOrder(1);

	//sprite->SetOrigin(82.5f, 69.0f);

	object->GetTransform()->SetPosition(200.0f, 200.0f);

	ce::Collider* collBox = object->AddComponent<ce::Collider>();

	collBox->SetFitSprite(true, true);

	ce::GameObject* object2 = new ce::GameObject();
	ce::Sprite* sprite2 = object2->AddComponent<ce::Sprite>();
	sprite2->SetSprite("image.jpg");
	sprite->SetDrawOrder(1);
	object2->GetTransform()->SetPosition(200.0f, 400.0f);
	ce::Collider* collBox2 = object2->AddComponent<ce::Collider>();
	collBox2->SetFitSprite(true, false);


	/*b2Vec2 gravity(0.0f, 0.0f);
	b2World world(gravity);
	b2BodyDef bodyDef;
	bodyDef.position.Set(100.0f, 100.0f);
	b2Body* body = world.CreateBody(&bodyDef);*/

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

		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			object->GetTransform()->SetPosition(object->GetTransform()->GetPosition() + sf::Vector2f(-10.0f, 0));
			//object->GetTransform()->Move(sf::Vector2f(-3000.0f, 0.0f));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			object->GetTransform()->SetPosition(object->GetTransform()->GetPosition() + sf::Vector2f(10.0f, 0));
			//object->GetTransform()->Move(sf::Vector2f(3000.0f, 0.0f));
        }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			object->GetTransform()->SetPosition(object->GetTransform()->GetPosition() + sf::Vector2f(0, -10.0f));
			//object->GetTransform()->Move(sf::Vector2f(0.0f, -3000.0f));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			object->GetTransform()->SetPosition(object->GetTransform()->GetPosition() + sf::Vector2f(0, 10.0f));
			//object->GetTransform()->Move(sf::Vector2f(0.0f, 3000.0f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			object->GetTransform()->Rotate(5.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			object->GetTransform()->Rotate(-5.0f);
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			object2->GetTransform()->SetPosition(object2->GetTransform()->GetPosition() + sf::Vector2f(-10.0f, 0));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			object2->GetTransform()->SetPosition(object2->GetTransform()->GetPosition() + sf::Vector2f(10.0f, 0));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			object2->GetTransform()->SetPosition(object2->GetTransform()->GetPosition() + sf::Vector2f(0, -10.0f));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			object2->GetTransform()->SetPosition(object2->GetTransform()->GetPosition() + sf::Vector2f(0, 10.0f));
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
		collManager->UpdateCollision();

		window.clear(sf::Color::Cyan);
		drawManager->Draw(window);
		window.display();


	}

	return 0;
}