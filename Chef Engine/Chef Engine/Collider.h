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
		void FitSprite();
		void SetGameObject(GameObject* gameObject);

	private:
		b2PolygonShape shape;
		//std::vector<b2Vec2> vertices;
		ce::Sprite* sprite;
		ce::Transform* transform;
		sf::Vector2f& transPos;
		sf::Vector2f& transScale;
		float spriteSizeX;
		float spriteSizeY;
		sf::Vector2f& spriteOrigin;
		bool fitSprite;
	};
}