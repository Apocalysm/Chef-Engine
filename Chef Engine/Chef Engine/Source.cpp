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

//////////////////////////////////////////////
///   \mainpage Main Page
///
///   This is documentation for how to use Lua scripts with Chef Engine.
///    
///   In the 'Modules' category, you will find a number of tutorials on how to use Lua with Chef Engine.\n
///   This includes things such as: 'How to create and use your own Component type in Lua' and 'Using the main loop in Lua'.\n
///   These tutorials show code examples and what the code does.\n
///   If you, as a designer, feels something is missing from these tutorials, ask me, Oskar, and I will fix it ASAP!
//////////////////////////////////////////////
#if _DEBUG
int main(int argc, char* argv[])
#else
int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#endif
{
    // Binds all defined classes with LuaBridge
    ce::LuaBridgeBinder::BindAll();

	ce::MapHandler* map = new ce::MapHandler;

    ce::GameObjectManager* objManager = new ce::GameObjectManager();
	ce::DrawEventManager* drawManager = new ce::DrawEventManager();

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Test");
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

        objManager->CallUpdate();
        if (ce::Camera::main != nullptr)
        {
            window.setView(ce::Camera::main->GetView());
        }
        window.clear(sf::Color::Cyan);
		drawManager->Draw(window);
		window.display();
	}

	return 0;
}