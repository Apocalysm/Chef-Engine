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
		// Calls the OnTriggerEnter event and passes the colliding collider
		collA->OnTriggerEnter(collB);
	}

	// If the collider of the second body is a trigger
	if (collB->GetIsTrigger())
	{
		// Calls the OnTriggerEnter event and passes the colliding collider
		collB->OnTriggerEnter(collA);
	}

	// If none of the colliders are triggers
	if (!collB->GetIsTrigger() && !collA->GetIsTrigger())
	{
		// Calls the OnCollisionEnter event and passes the colliding collider
		collA->OnCollisionEnter(collB);
		collB->OnCollisionEnter(collA);
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
		// Calls the OnTriggerExit event and passes the collider that stopped colliding
		collA->OnTriggerExit(collB);
	}

	// If the collider of the second body is a trigger
	if (collB->GetIsTrigger())
	{
		// Calls the OnTriggerExit event and passes the collider that stopped colliding
		collB->OnTriggerExit(collA);
	}

	if (!collB->GetIsTrigger() && !collA->GetIsTrigger())
	{
		// Calls the OnCollisionExit event and passes the collider that stopped colliding
		collA->OnCollisionExit(collB);
		collB->OnCollisionExit(collA);
	}
}
