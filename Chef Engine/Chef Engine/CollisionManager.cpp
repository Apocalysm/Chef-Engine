#include "CollisionManager.h"
#include "Collider.h"
#include "GameObject.h"

b2World* ce::CollisionManager::world;

std::map<Common::uint64, ce::Collider*> ce::CollisionManager::intToCollider;
//std::map<Common::uint64, ce::Collider*> ce::CollisionManager::intToNewRectangles;

using ce::CollisionManager;


CollisionManager::CollisionManager()
{
	// Zeroes gravity
	gravity.Set(0.0f, 0.0f);

	// Creates the physics world
	world = new b2World(gravity);
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
	world->Step(1, 8, 30);

	for (auto it = intToCollider.begin(); it != intToCollider.end(); it++)
	{
		ce::Collider* coll = it->second;

		// Positions to be moved to
		float posX;
		float posY;

		// If the collider should fit a sprite
		if (coll->fitSprite)
		{
			// Gets the position of the body with an offset since the transform should not be directly at the bodys position
			posX = coll->body->GetPosition().x - coll->spriteSizeX / 2 * coll->transScale.x + coll->spriteOrigin.x * coll->transScale.x;
			posY = coll->body->GetPosition().y - coll->spriteSizeY / 2 * coll->transScale.y + coll->spriteOrigin.y * coll->transScale.y;

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