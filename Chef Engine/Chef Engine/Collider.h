#pragma once

#include "Component.h"
#include "Sprite.h"

#include <Box2D/Box2D.h>

namespace ce
{
	class Collider : public ce::Component
	{
	public:
		Collider();
		~Collider();

		void Update();

		// Creates a collision box based on the Vector2 values
		// Should only be called when creating collision boxes from Tiled
		void SetupTMX(const sf::Vector2f rectSize, const bool dynamic, const bool isTrigger);

		// Creates a collision box based on the sprite component attached to the same gameobject this component is attached to
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

		// Is called when this collider begins to overlap another collider if this is a trigger
		virtual void OnTriggerEnter(Collider* other);

		// Is called when this collider stops to overlap
		virtual void OnTriggerExit(Collider* other);

	private:
		friend class CollisionManager;
		friend class Transform;

		// Should the collider fit a sprite?
		bool fitSprite;

		// Is this collider a trigger?
		bool isTrigger;

		// Is a body created?
		bool bodyIsCreated;

		// Bodies is created from this
		b2BodyDef bodyDef;

		// Body holding collider and info
		b2Body* body;

		// Shape of the collider
		b2PolygonShape shape;

		// Fixtures is created from this
		b2FixtureDef fixtureDef;

		// Pointer to the sprite component that belongs the tha same gameobject as this component
		ce::Sprite* sprite;

		// Pointer to the transform component that belongs the tha same gameobject as this component
		ce::Transform* transform;

		sf::Vector2f transPos;

		sf::Vector2f transScale;

		float transRot;

		float spriteSizeX;

		float spriteSizeY;

		sf::Vector2f spriteOrigin;

		const double PI = 3.141592653589793;

		// Bridges parts of this script to Lua
		static void DoBind(lua_State* L);
	};
}