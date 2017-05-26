#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
#include "MapHandler.h"
#include "Sprite.h"
#include "GameObjectManager.h"
#include "DrawEventManager.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "Camera.h"
#include "ContactListener.h"

#include <SFML/Graphics.hpp>
#include <Tmx\TmxTile.h>

#include <Windows.h>
#include <typeinfo>
#include <iostream>
#include <vector>


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


	sf::RenderWindow window(sf::VideoMode(1280, 720), "Test");
	window.setFramerateLimit(60);

	ce::MapHandler* map = new ce::MapHandler;

    ce::GameObjectManager* objManager = new ce::GameObjectManager();
	ce::DrawEventManager* drawManager = new ce::DrawEventManager();
	ce::CollisionManager* collManager = new ce::CollisionManager();
	ce::ContactListener contactListener;
	collManager->GetWorld()->SetContactListener(&contactListener);

	ce::GameObject* object = new ce::GameObject();

	object->SetName("RandomObject");

	object->GetTransform()->SetPosition(150, 150);

	ce::Sprite* sprite = object->AddComponent<ce::Sprite>();
	sprite->SetSprite("Player.png");
	sprite->SetDrawOrder(1);

	ce::Collider* collider = object->AddComponent<ce::Collider>();
	collider->SetFitSprite(true, true, false);

	ce::Camera* camera = object->AddComponent<ce::Camera>();
	camera->SetSize(sf::Vector2f(128 * 2, 72 * 2));
	camera->SetFollow(true);
	//camera->SetZoom(0.001);


	ce::GameObject* dot1 = new ce::GameObject();
	dot1->GetTransform()->SetPosition(140, 150);
	ce::Sprite* dot1Spr = dot1->AddComponent<ce::Sprite>();
	dot1Spr->SetSprite("dot.png");
	dot1Spr->SetDrawOrder(5);
	ce::Collider* dot1Coll = dot1->AddComponent<ce::Collider>();
	dot1Coll->SetFitSprite(true, false, false);

	ce::GameObject* dot2 = new ce::GameObject();
	dot2->GetTransform()->SetPosition(150, 140);
	ce::Sprite* dot2Spr = dot2->AddComponent<ce::Sprite>();
	dot2Spr->SetSprite("dot.png");
	dot2Spr->SetDrawOrder(5);
	ce::Collider* dot2Coll = dot2->AddComponent<ce::Collider>();
	dot2Coll->SetFitSprite(true, false, false);

	ce::GameObject* dot3 = new ce::GameObject();
	dot3->GetTransform()->SetPosition(160, 150);
	ce::Sprite* dot3Spr = dot3->AddComponent<ce::Sprite>();
	dot3Spr->SetSprite("dot.png");
	dot3Spr->SetDrawOrder(5);
	ce::Collider* dot3Coll = dot3->AddComponent<ce::Collider>();
	dot3Coll->SetFitSprite(true, false, true);

	dot2->Destroy();

    float count = 5;
    float timer = 0;
	
	map->LoadMap("RefferenceMap.tmx");
	std::string* mapName = new std::string("RefferenceMap.tmx");
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
        
        if (timer >= count)
        {          
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
                object->GetTransform()->Move(sf::Vector2f(0, -1));
                timer = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
                object->GetTransform()->Move(sf::Vector2f(0, 1)); timer = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
                object->GetTransform()->Move(sf::Vector2f(-1, 0)); timer = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
                object->GetTransform()->Move(sf::Vector2f(1, 0)); timer = 0;
            }

			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				camera->SetZoom(0.001);
			}*/
        }
        else
            timer += 1;

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
		camera->Update();
		window.setView(camera->GetView());

		window.clear(sf::Color::Cyan);
		drawManager->Draw(window);
		window.display();
	}

	return 0;
}