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

////////////////////////////////////////////////////////////
//
// Author: Dennis Karlsson
//
////////////////////////////////////////////////////////////


#include "CollisionManager.h"
#include "Collider.h"
#include "Transform.h"
#include "Sprite.h"
#include "GameObject.h"

#include <Box2D\Box2D.h>

b2World* ce::CollisionManager::world = 0;

std::map<uint64, ce::Collider*> ce::CollisionManager::intToCollider;
//std::map<uint64, ce::Collider*> ce::CollisionManager::intToNewRectangles;

using ce::CollisionManager;


CollisionManager::CollisionManager()
    : gravity(new b2Vec2(0, 0))
{
    world = new b2World(*gravity);

    /*
     Zeroes gravity
    gravity = new b2Vec2(0, 0);

	 Creates the physics world
	world = new b2World(*gravity);*/
}


CollisionManager::~CollisionManager()
{
}


b2World* ce::CollisionManager::GetWorld()
{
	return world;
}


void ce::CollisionManager::AddCollider(ce::Collider* collider)
{
	// Adds a collider component to the map with the same key as the ID of the gameobject owning the component
	intToCollider.insert(std::make_pair(collider->gameObject->GetID(), collider));
}


void ce::CollisionManager::RemoveCollider(ce::Collider* collider)
{
	if (collider != nullptr)
	{
		const unsigned long long ID = collider->gameObject->GetID();

		// Erases the collider at the right key
		intToCollider.erase(ID);

		// Destroys the body in the world
		world->DestroyBody(collider->body);
	}
}


void ce::CollisionManager::UpdateCollision()
{
	// Takes a step at calculating physics
	world->Step(1, 8, 300);

	for (auto it = intToCollider.begin(); it != intToCollider.end(); it++)
	{
		if (!it->second->isTrigger)
		{
			ce::Collider* coll = it->second;

			// Positions to be moved to
			float posX;
			float posY;

			// If the collider should fit a sprite
			if (coll->fitSprite)
			{
				// Gets the position of the body with an offset since the transform should not be directly at the bodys position
				posX = coll->body->GetPosition().x - coll->spriteSize.x / 2 * coll->transScale.x + coll->spriteOrigin.x * coll->transScale.x;
				posY = coll->body->GetPosition().y - coll->spriteSize.y / 2 * coll->transScale.y + coll->spriteOrigin.y * coll->transScale.y;

				// Moves the transform component to the calculated position
				coll->transform->SetPosition(posX, posY);

				// Updates the sprites since it should be moved to the transforms ne position
				coll->gameObject->GetComponent<ce::Sprite>()->Update();
			}
			else
			{
				// Gets the position of the body
				posX = coll->body->GetPosition().x;
				posY = coll->body->GetPosition().y;

				// Moves the transform to the same position of the body
				coll->transform->SetPosition(posX, posY);
			}
		}
	}
}