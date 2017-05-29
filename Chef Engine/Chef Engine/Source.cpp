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
#include "SFMLKeyboard.h"

#include <SFML/Graphics.hpp>
#include <Tmx\TmxTile.h>

#include <Windows.h>
#include <typeinfo>
#include <iostream>
#include <vector>

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
	//ce::MapHandler* map = new ce::MapHandler;

    ce::GameObjectManager* objManager = new ce::GameObjectManager();
	ce::DrawEventManager* drawManager = new ce::DrawEventManager();

	ce::CollisionManager* collManager = new ce::CollisionManager();
	ce::ContactListener contactListener;
	collManager->GetWorld()->SetContactListener(&contactListener);


	sf::RenderWindow window(sf::VideoMode(1280, 720), "Test");
    ce::Camera::window = &window;
    window.setFramerateLimit(60);

    window.setKeyRepeatEnabled(false);
    ce::SFMLKeyboard::Initialize();

    // Binds all defined classes with LuaBridge
    ce::LuaBridgeBinder::BindAll();

	while (window.isOpen())
	{
		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                ce::SFMLKeyboard::SetKeyDown(event.key.code);
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                ce::SFMLKeyboard::SetKeyUp(event.key.code);
            }
            else if (event.type == sf::Event::LostFocus || event.type == sf::Event::GainedFocus)
            {
                ce::SFMLKeyboard::ResetKeyboard();
            }
        }

		window.clear(sf::Color::Cyan);
        
        // Calls our main-loop in Lua
        (*ce::LuaBridgeBinder::mainFunc)();

        objManager->CallUpdate();
		
        collManager->UpdateCollision();

        // Updates the camera if there is one
        if (ce::Camera::main != nullptr)
        {
            ce::Camera::main->UpdateCamera();
        }

		drawManager->Draw(window);

		window.display();

		ce::SFMLKeyboard::ClearKeys();
	}

	return 0;
}