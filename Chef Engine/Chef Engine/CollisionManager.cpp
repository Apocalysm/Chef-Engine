#include "CollisionManager.h"
#include "Collider.h"
#include "GameObject.h"

b2World* ce::CollisionManager::world;

std::map<Common::uint64, ce::Collider*> ce::CollisionManager::intToRectangles;
//std::map<Common::uint64, ce::Collider*> ce::CollisionManager::intToNewRectangles;

using ce::CollisionManager;


CollisionManager::CollisionManager()
{
	gravity.Set(0.0f, 0.0f);
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
	intToRectangles.insert(std::make_pair(collider->gameObject->GetID(), collider));
}


void ce::CollisionManager::RemoveCollider(ce::Collider* collider)
{
	if (collider != nullptr)
	{
		const unsigned long long ID = collider->gameObject->GetID();

		// Erases the collider from the map it belongs to
		/*if (collider->isNew)
			intToNewRectangles.erase(ID);
		else*/
			intToRectangles.erase(ID);
	}
}


void ce::CollisionManager::UpdateCollision()
{
	world->Step(1, 8, 300);

	for (auto it = intToRectangles.begin(); it != intToRectangles.end(); it++)
	{
		ce::Collider* coll = it->second;

		float posX;
		float posY;

		if (coll->fitSprite)
		{
			posX = coll->body->GetPosition().x - coll->spriteSizeX / 2 * coll->transScale.x + coll->spriteOrigin.x * coll->transScale.x;
			posY = coll->body->GetPosition().y - coll->spriteSizeY / 2 * coll->transScale.y + coll->spriteOrigin.y * coll->transScale.y;

			coll->transform->SetPosition(posX, posY);

			coll->gameObject->GetComponent<ce::Sprite>()->Update();
		}
		else
		{
			posX = coll->body->GetPosition().x;
			posY = coll->body->GetPosition().y;

			coll->transform->SetPosition(posX, posY);
		}
	}
}


