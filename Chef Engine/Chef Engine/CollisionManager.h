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


#pragma once
#include "Common.h"

#include <map>

class b2World;
struct b2Vec2;

namespace ce
{
	class Collider;
	class ContactListener;

	class CollisionManager
	{
	public:
		CollisionManager();
		~CollisionManager();

		// Returns the world holding bodies and handling physics
        CHEF_API static b2World* GetWorld();

		static void AddCollider(ce::Collider* collider);
		static void RemoveCollider(ce::Collider* collider);

        CHEF_API static void UpdateCollision();
		

	private:
		// Map with colliders
		static std::map<uint64, ce::Collider*> intToCollider;

		b2Vec2* gravity;

		// Holds bodies and handles physics
		static b2World* world;

		ce::ContactListener* contactListener;
	};
}
