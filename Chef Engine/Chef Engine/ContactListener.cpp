#include "ContactListener.h"
#include "Collider.h"
#include "GameObject.h"

using ce::ContactListener;


ce::ContactListener::ContactListener()
{
}


ce::ContactListener::~ContactListener()
{
}


void ce::ContactListener::BeginContact(b2Contact* contact)
{
	// Gets the user data from both bodies
	void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();

	// Casts the user info to pointers to Collider components
	ce::Collider* collA = static_cast<ce::Collider*>(bodyAUserData);
	ce::Collider* collB = static_cast<ce::Collider*>(bodyBUserData);

	// If the collider of the first body is a trigger
	if (collA->GetIsTrigger())
	{
		// Calls the potential OnTriggerEnter functions in lua components
		// The function takes a pointer to the other objects Collider component
		for (auto component : collA->GetGameObject()->luaComponents)
		{
            component.second->OnTriggerEnter(collB);
		}
	}

	// If the collider of the second body is a trigger
	if (collB->GetIsTrigger())
	{
		// Calls the potential OnTriggerEnter functions in lua components
		// The function takes a pointer to the other objects Collider component
        for (auto component : collB->GetGameObject()->luaComponents)
        {
            component.second->OnTriggerEnter(collA);
        }
	}

	// If none of the colliders are triggers
	if (!collB->GetIsTrigger() && !collA->GetIsTrigger())
	{
		// Calls the potential OnCollisionEnter functions in lua components
		// The function takes a pointer to the other objects Collider component
        for (auto component : collA->GetGameObject()->luaComponents)
        {
            component.second->OnCollisionEnter(collB);
        }
        for (auto component : collB->GetGameObject()->luaComponents)
        {
            component.second->OnCollisionEnter(collA);
        }
	}
}


void ce::ContactListener::EndContact(b2Contact* contact)
{
	// Gets the user data from both bodies
	void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();

	// Casts the user info to pointers to Collider components
	ce::Collider* collA = static_cast<ce::Collider*>(bodyAUserData);
	ce::Collider* collB = static_cast<ce::Collider*>(bodyBUserData);

	// If the collider of the first body is a trigger
	if (collA->GetIsTrigger())
	{
		// Calls the potential OnTriggerExit functions in lua components
		// The function takes a pointer to the other objects Collider component
        for (auto component : collA->GetGameObject()->luaComponents)
        {
            component.second->OnTriggerExit(collB);
        }
	}

	// If the collider of the second body is a trigger
	if (collB->GetIsTrigger())
	{
		// Calls the potential OnTriggerExit functions in lua components
		// The function takes a pointer to the other objects Collider component
        for (auto component : collB->GetGameObject()->luaComponents)
        {
            component.second->OnTriggerExit(collA);
        }
	}
	
    if (!collB->GetIsTrigger() && !collA->GetIsTrigger())
	{
		// Calls the potential OnCollisionExit functions in lua components
		// The function takes a pointer to the other objects Collider component
        for (auto component : collA->GetGameObject()->luaComponents)
        {
            component.second->OnCollisionExit(collB);
        }
        for (auto component : collB->GetGameObject()->luaComponents)
        {
            component.second->OnCollisionExit(collA);
        }
	}
}
