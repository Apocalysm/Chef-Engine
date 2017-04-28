#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
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
	LuaBridgeBinder::BindAll();

	sf::RenderWindow window(sf::VideoMode(300, 300), "Test");

	ce::GameObjectManager* objManager = new ce::GameObjectManager();
	ce::DrawEventManager* drawManager = new ce::DrawEventManager();

	ce::GameObject* object = new ce::GameObject("object");

	ce::Sprite* sprite = object->AddComponent<ce::Sprite>();
	sprite->SetSprite("image");

	object->GetTransform()->SetPosition(100, 100);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		objManager->CallUpdate();

		window.clear();
		drawManager->Draw(window);
		window.display();
	}

	return 0;
}