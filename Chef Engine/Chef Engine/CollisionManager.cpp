#include "CollisionManager.h"
#include "Collider.h"
#include "GameObject.h"

//b2World* ce::CollisionManager::world;

std::map<Common::uint64, ce::Collider*> ce::CollisionManager::intToRectangles;
std::map<Common::uint64, ce::Collider*> ce::CollisionManager::intToNewRectangles;

using ce::CollisionManager;


CollisionManager::CollisionManager()
{
	/*gravity.SetZero();
	world = new b2World(gravity);*/
}


CollisionManager::~CollisionManager()
{
}


//b2World* ce::CollisionManager::GetWorld()
//{
//	return world;
//}


void ce::CollisionManager::AddCollider(ce::Collider* collider)
{
	intToNewRectangles.insert(std::make_pair(collider->gameObject->GetID(), collider));
}


void ce::CollisionManager::RemoveCollider(ce::Collider* collider)
{
	if (collider != nullptr)
	{
		const unsigned long long ID = collider->gameObject->GetID();

		// Erases the collider from the map it belongs to
		if (collider->isNew)
			intToNewRectangles.erase(ID);
		else
			intToRectangles.erase(ID);
	}
}


void ce::CollisionManager::UpdateCollision()
{
	//world->Step(1.0f / 60.0f, 8, 3);
	for (auto it = intToRectangles.begin(); it != intToRectangles.end(); it++)
	{

	}
}


