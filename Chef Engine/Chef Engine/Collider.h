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


#pragma once
#include "Component.h"
#include "Common.h"
#include "LuaBridgeBinder.h"

#include "Vec2.h"

struct b2BodyDef;
class b2Body;
class b2PolygonShape;
struct b2FixtureDef;

struct lua_State;

namespace ce
{
    class Sprite;

    ////////////////////////////////////////////////////////////
    /// \brief Component that allows for collision with other GameObjects
    /// Add a Collider to a GameObject with GameObject:AddCollider()
    /// \code
    /// --Creates a GameObject and adds a Collider to it
    ///
    /// object = Chef.GameObject("name")
    ///
    /// collider = object:AddCollider() 
    /// \endcode
    /// 
    /// \n Tries to get a Collider from a GameObject with GameObject:GetCamera()
    /// \code
    /// --Gets a Collider from the GameObject "object"
    ///
    /// collider = object:GetCollider()
    /// \endcode
    ///
    /// \n Remove a Collider from a GameObject with GameObject:RemoveCamera()
    /// \code
    /// --Tries to remove a Collider from the GameObject "object"
    ///
    /// object:RemoveCollider()
    /// \endcode
    ////////////////////////////////////////////////////////////
	class Collider : public ce::Component
	{
        // Befriends the templated Bind function so it can access our protected functions
        friend void LuaBridgeBinder::Bind<ce::Collider>(lua_State*);

	public:
        ////////////////////////////////////////////////////////////
        /// \brief Default Collider Constructor.
        /// In Lua you use GameObject:AddCollider()
        /// \code
        /// --Creates a GameObject and adds a Collider to it
        ///
        /// object = Chef.GameObject("name")
        ///
        /// collider = object:AddCollider()
        /// \endcode
        ////////////////////////////////////////////////////////////
		Collider();
		~Collider();

		void Update();

		// Creates a collision box based on the Vector2 values
		// Should only be called when creating collision boxes from Tiled
		void SetupTMX(const Vec2f& rectSize, const bool dynamic, const bool isTrigger);

        ////////////////////////////////////////////////////////////
        /// \brief Creates a collision box based on the sprite component attached to the same gameobject this component is attached to
        /// \code
        /// --Adds a Collider component to an object and then fits the Collision box to that object's Sprite
        ///
        /// collider = object:AddCollider()
        /// collider:SetFitSprite() 
        /// \endcode
        ////////////////////////////////////////////////////////////
		void SetFitSprite(const bool fitSprite, const bool dynamic, const bool isTrigger);

		// Sets if the collider should be a trigger or not
		// Being a trigger means that the object can go through other colliders
		void SetIsTrigger(const bool isTrigger);

		bool GetIsTrigger() const;

		void SetGameObject(GameObject* gameObject);

		// Is called when this collider begins to collide with another collider that isn't a trigger
		virtual void OnCollisionEnter(Collider* other);

		// Is called when this collider stops colliding
		virtual void OnCollisionExit(Collider* other);

		// Is continuously called when this collider collide with another collider that isn't a trigger
		virtual void OnCollisionStay(Collider* other);

		// Is called when this collider begins to overlap another collider if this is a trigger
		virtual void OnTriggerEnter(Collider* other);

		// Is called when this collider stops to overlap
		virtual void OnTriggerExit(Collider* other);

		// Is continuously called when this collider overlaps another collider if this is a trigger
		virtual void OnTriggerStay(Collider* other);

	private:
		friend class CollisionManager;
		friend class Transform;

		// Should the collider fit a sprite?
		bool fitSprite;

		/// \brief If the collider is a trigger, that basically means it goes through other objects but still trigger Collisions
		bool isTrigger;

		// Is a body created?
		bool bodyIsCreated;

		// Is the collider currently colliding?
		bool isColliding;

		// Bodies is created from this
		b2BodyDef* bodyDef;

		// Body holding collider and info
		b2Body* body;

		// Shape of the collider
		b2PolygonShape* shape;

		// Fixtures is created from this
		b2FixtureDef* fixtureDef;

		// Pointer to the sprite component that belongs the tha same gameobject as this component
		ce::Sprite* sprite;

		// Pointer to the transform component that belongs the tha same gameobject as this component
		ce::Transform* transform;

		Vec2f transPos;

		Vec2f transScale;

		float transRot;

        Vec2u spriteSize;

		Vec2f spriteOrigin;

		// Contains pointers to colliders that this collider is currently colliding with
		std::map<uint64, ce::Collider*> collidingColls;

		const double PI = 3.141592653589793;

		// Bridges parts of this script to Lua
		static void DoBind(lua_State* L);
	};
}
