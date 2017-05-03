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

	int tempTimer = 0;
	int tempTimer2 = 0;
	int tempTimer3 = 0;
	int temptimer4 = 0;

	bool tempBool = true;

	std::vector<ce::GameObject*> tempVector;
	ce::GameObject* obj = new ce::GameObject("obj");
	tempVector.push_back(obj);

	for (int i = 0; i < 10; i++)
	{
		ce::GameObject* object5 = new ce::GameObject("object");
		tempVector.push_back(object5);
		ce::Sprite* sprite5 = object5->AddComponent<ce::Sprite>();
		sprite5->SetSprite("image.jpg");
		sprite5->SetDrawOrder(0);
	}

	for (int i = 0; i < 10; i++)
	{
		ce::GameObject* object = new ce::GameObject("object");
		tempVector.push_back(object);
		ce::Sprite* sprite = object->AddComponent<ce::Sprite>();
		sprite->SetSprite("image2.jpg");
		sprite->SetDrawOrder(1);
		object->GetComponent<ce::Transform>()->SetPosition(50, 0);
	}



	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		objManager->CallUpdate();

		/*if (temptimer4 == 100)
		{
			for (auto it = tempVector.begin(); it != tempVector.end();)
			{
				(*it)->Destroy();
				it = tempVector.erase(it);
			}

			tempVector.clear();
			tempVector.shrink_to_fit();
			
		}
		temptimer4++;*/

		window.clear();
		drawManager->Draw(window);
		window.display();
	}

	return 0;
}