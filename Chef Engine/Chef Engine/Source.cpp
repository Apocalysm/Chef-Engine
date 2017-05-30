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
#include "SoundManager.h"

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

	ce::MapHandler* map = new ce::MapHandler();

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Test");

	ce::SoundManager* sM = new ce::SoundManager("sound.wav");
	ce::SoundManager* sM2 = new ce::SoundManager("sound2.wav");

	ce::MapHandler* map = new ce::MapHandler(); 

	window.setFramerateLimit(60);
    float count = 10;
    float timer = 0;
    ce::Camera::window = &window;

	map->LoadMap("RefferenceMap.tmx");
	std::string* mapName = new std::string("RefferenceMap.tmx");
	map->RegisterMap(0, mapName);
	map->LoadObject();

	window.setKeyRepeatEnabled(false);
	ce::SFMLKeyboard::Initialize();
	sf::SoundBuffer buffer3;
	sf::Sound* sound = new sf::Sound();
	sf::Sound* buffer2 = new sf::Sound();
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

		if (ce::SFMLKeyboard::GetKeyDown(sf::Keyboard::M))
		{
			sM->PlaySFXSOUND();
		}
		else if (ce::SFMLKeyboard::GetKeyDown(sf::Keyboard::N))
		{
			sM2->PlaySFXSOUND();
		}
		else if (ce::SFMLKeyboard::GetKeyUp(1))
		{
		}
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