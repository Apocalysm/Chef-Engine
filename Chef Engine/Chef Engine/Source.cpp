#include "Component.h"
#include "GameObject.h"
#include "Transform.h"

#include <Windows.h>
#include <typeinfo>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <Tmx\TmxTile.h>

#if _DEBUG
int main()
#else
int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#endif
{
	ce::GameObject obj("hej");

	ce::Transform* transform = obj.AddComponent<ce::Transform>();

	std::cout << transform->GetPosition().x << " " << transform->GetPosition().y << std::endl;
	transform->SetPosition(2, 3);
	std::cout << transform->GetPosition().x << " " << transform->GetPosition().y << std::endl;

	return 0;
}