////////////////////////////////////////////////////////////
//
// Chef Engine
// Copyright (C) 2017 Oskar Svensson
//  
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////


#include "ContactListener.h"
#include "Collider.h"
#include "GameObject.h"

#include <Box2D\Dynamics\Contacts\b2Contact.h>

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
