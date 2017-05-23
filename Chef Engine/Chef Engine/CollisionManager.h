#pragma once
#include "Common.h"

#include <Box2D/Box2D.h>

#include <map>


namespace ce
{
	class Collider;

	class CollisionManager
	{
	public:
		CollisionManager();
		~CollisionManager();

		// Returns the world holding bodies and handling physics
		static b2World* GetWorld();

		static void AddCollider(ce::Collider* collider);
		static void RemoveCollider(ce::Collider* collider);

		void UpdateCollision();
		

	private:
		// Map with colliders
		static std::map<Common::uint64, ce::Collider*> intToCollider;

		b2Vec2 gravity;

		// Holds bodies and handles physics
		static b2World* world;
	};
}
