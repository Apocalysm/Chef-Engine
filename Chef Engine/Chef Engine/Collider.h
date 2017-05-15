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

		void SetupTMX(const sf::RectangleShape rectShape);

		void SetupFitSprite();

		void SetPosition(const float x, const float y);

		void SetRotation(const float angle);

		void SetScale(const float x, const float y);

		void SetOrigin(const float x, const float y);

		void SetGameObject(GameObject* gameObject);

		void SetIsTrigger(const bool isTrigger);

		bool GetIsTrigger() const;


	private:
		friend class CollisionManager;

		bool fitSprite;
		bool isTrigger;
		bool isNew;
		sf::RectangleShape shape;
		sf::Sprite* sprite;
		sf::Vector2f size;

		//b2BodyDef bodyDef;
		//b2Body* body;
		//b2PolygonShape shape;
		////std::vector<b2Vec2> vertices;
		//ce::Sprite* sprite;
		//ce::Transform* transform;
		//sf::Vector2f& transPos;
		//sf::Vector2f& transScale;
		//float transRot;
		//float spriteSizeX;
		//float spriteSizeY;
		//sf::Vector2f& spriteOrigin;

		//const double PI = 3.141592653589793;
	};
}