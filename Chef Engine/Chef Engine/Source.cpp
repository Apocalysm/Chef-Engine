#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
#include "MapHandler.h"
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

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Test");

	ce::MapHandler* map = new ce::MapHandler;


	map->LoadMap("sewers.tmx");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		objManager->CallUpdate();

		if (tempTimer == 1)
		{
			object->GetTransform()->SetPosition(object->GetTransform()->GetPosition().x + 1, object->GetTransform()->GetPosition().y);
			object->GetComponent<ce::Sprite>()->SetRotation(object->GetComponent<ce::Sprite>()->GetRotation() + 1);
			tempTimer = 0;
		}
		tempTimer++;

		if (tempTimer2 == 5 && tempBool)
		{
			object2->GetTransform()->SetPosition(object2->GetTransform()->GetPosition().x + 3, object2->GetTransform()->GetPosition().y-5);
			object2->GetComponent<ce::Sprite>()->SetRotation(object->GetComponent<ce::Sprite>()->GetRotation() -6);
			tempTimer2 = 0;
		}
		tempTimer2++;

		if (tempTimer3 == 1)
		{
			object3->GetTransform()->SetPosition(object3->GetTransform()->GetPosition().x -1, object3->GetTransform()->GetPosition().y-10);
			object3->GetComponent<ce::Sprite>()->SetRotation(object3->GetComponent<ce::Sprite>()->GetRotation() + 7);
			tempTimer3 = 0;
		}
		tempTimer3 = 0;

		if (temptimer4 == 100)
		{
			for (auto it = tempVector.begin(); it != tempVector.end();)
			{
				(*it)->Destroy();
				it = tempVector.erase(it);
			}

			tempVector.clear();
		}
		temptimer4++;

		window.clear();
		map->DrawMap(window);
		window.display();


	}

	return 0;
}