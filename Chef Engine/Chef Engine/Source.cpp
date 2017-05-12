#include "Component.h"
#include "Transform.h"
#include "Sprite.h"
#include "LuaComponent.h"

#include "GameObject.h"

#include "MapHandler.h"
#include "GameObjectManager.h"
#include "DrawEventManager.h"

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

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Test");

    window.setFramerateLimit(60);

	ce::MapHandler* map = new ce::MapHandler;

    ce::GameObjectManager* objManager = new ce::GameObjectManager();
	ce::DrawEventManager* drawManager = new ce::DrawEventManager();

	ce::GameObject* object = new ce::GameObject();

	//auto* sprite = object->AddComponent<ce::GameObjectManager>();

	//sprite->SetSprite("ThreeByThree.png");*/
	
	//sprite->SetDrawOrder(1);

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    ce::LuaComponent* newComponent = object->AddLuaComponent(L, new std::string("Lua Scripts\\Components\\NewComponent.lua"), new std::string("NewComponent"));

	map->LoadMap("orthogonal-outside.tmx");
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
            object->GetTransform()->SetScale(object->GetTransform()->GetScale() + sf::Vector2f(0.003f, 0.003f));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
        {
            object->GetTransform()->SetScale(object->GetTransform()->GetScale() - sf::Vector2f(0.003f, 0.003f));
        }*/

        objManager->CallUpdate();

		window.clear(sf::Color::Cyan);
		//drawManager->Draw(window);
		window.display();


	}

	return 0;
}