#include "CollisionManager.h"

using ce::CollisionManager;


CollisionManager::CollisionManager()
{
	gravity.SetZero();
	world = new b2World(gravity);
}


CollisionManager::~CollisionManager()
{
}

b2World* ce::CollisionManager::GetWorld()
{
	return world;
}


