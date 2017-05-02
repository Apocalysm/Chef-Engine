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
	sprite->SetSprite("image.jpg");

	object->GetTransform()->SetPosition(100, 100);



	ce::GameObject* object2 = new ce::GameObject("object");
	ce::Sprite* sprite2 = object2->AddComponent<ce::Sprite>();
	sprite2->SetSprite("image.jpg");

	ce::GameObject* object3 = new ce::GameObject("object");
	ce::Sprite* sprite3 = object3->AddComponent<ce::Sprite>();
	sprite3->SetSprite("image.jpg");

	ce::GameObject* object4 = new ce::GameObject("object");
	ce::Sprite* sprite4 = object4->AddComponent<ce::Sprite>();
	sprite4->SetSprite("image.jpg");

	int tempTimer = 0;
	int tempTimer2 = 0;
	int tempTimer3 = 0;
	int temptimer4 = 0;

	bool tempBool = true;

	std::vector<ce::GameObject*> tempVector;

	for (int i = 0; i < 1000; i++)
	{
		ce::GameObject* object2 = new ce::GameObject("object");
		tempVector.push_back(object2);
		ce::Sprite* sprite2 = object2->AddComponent<ce::Sprite>();
		sprite2->SetSprite("image.jpg");
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
		drawManager->Draw(window);
		window.display();
	}

	return 0;
}