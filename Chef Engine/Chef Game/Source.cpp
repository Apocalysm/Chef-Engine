#include <GameObject.h>
#include <Component.h>
#include <Transform.h>
#include <Sprite.h>
#include <Camera.h>
#include <Collider.h>
#include <DrawableComponent.h>

#include <GameObjectManager.h>
#include <DrawEventManager.h>
#include <CollisionManager.h>
#include <ContactListener.h>
#include <MapHandler.h>
#include <SFMLKeyboard.h>

#include <LuaBind.h>
#include <LuaBridgeBinder.h>

#include <SFML\Graphics.hpp>

#include <Windows.h>
#include <typeinfo>
#include <iostream>
#include <vector>


#if _DEBUG
int main(int argc, char* argv[])
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#endif
{
    //ce::MapHandler* map = new ce::MapHandler;

    ce::GameObjectManager* objManager = new ce::GameObjectManager();
    ce::DrawEventManager* drawManager = new ce::DrawEventManager();

    ce::CollisionManager* collManager = new ce::CollisionManager();
    ce::ContactListener contactListener;
    collManager->GetWorld()->SetContactListener(&contactListener);


    sf::RenderWindow window(sf::VideoMode(1280, 720), "Election Day");
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
        if (ce::LuaBridgeBinder::mainFunc)
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