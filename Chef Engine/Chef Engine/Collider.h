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

		void SetupTMX(const sf::RectangleShape* rectShape, const bool dynamic, const bool isTrigger);

		void SetFitSprite(const bool fitSprite, const bool dynamic, const bool isTrigger);

		void SetIsTrigger(const bool isTrigger);

		bool GetIsTrigger() const;

		void SetGameObject(GameObject* gameObject);

		virtual void OnCollision(GameObject* other);

		virtual void OnTrigger(GameObject* other);


	private:
		friend class CollisionManager;
		friend class Transform;

		bool fitSprite;
		bool isTrigger;
		bool isNew;
		//sf::FloatRect fRect;
		//sf::RectangleShape* shape;
		//sf::Sprite* sprite;
		//sf::Vector2f size;
		//sf::Vector2f deltaPos;
		//sf::Vector2f lastPos;
		//ce::Transform* transform;

		b2BodyDef bodyDef;
		b2Body* body;
		b2PolygonShape shape;
		b2FixtureDef fixtureDef;
		//std::vector<b2Vec2> vertices;
		ce::Sprite* sprite;
		ce::Transform* transform;
		sf::Vector2f transPos;
		sf::Vector2f transScale;
		float transRot;
		float spriteSizeX;
		float spriteSizeY;
		sf::Vector2f spriteOrigin;

		const double PI = 3.141592653589793;
	};
}