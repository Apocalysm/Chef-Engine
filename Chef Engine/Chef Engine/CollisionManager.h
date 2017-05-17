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
		static b2World* GetWorld();

		static void AddCollider(ce::Collider* collider);
		static void RemoveCollider(ce::Collider* collider);

		void UpdateCollision();
		

	private:
		// Map with colliders
		static std::map<Common::uint64, ce::Collider*> intToRectangles;

		//// Map with colliders recently created
		//static std::map<Common::uint64, ce::Collider*> intToNewRectangles;

		b2Vec2 gravity;
		static b2World* world;
	};
}
