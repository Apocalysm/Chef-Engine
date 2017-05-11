#include "Collider.h"
#include "GameObject.h"
#include "Sprite.h"

using ce::Collider;


Collider::Collider() : transPos(sf::Vector2f(0.0f, 0.0f)), transScale(sf::Vector2f(0.0f, 0.0f)), spriteOrigin(sf::Vector2f(0.0f, 0.0f))
{
	fitSprite = false;
}


Collider::~Collider()
{
}


void ce::Collider::Update()
{
	if (fitSprite)
	{
		b2Vec2 vertices[4];

		vertices[0].Set(transform->GetPosition().x - spriteOrigin.x,
			transform->GetPosition().y - spriteOrigin.y);

		vertices[1].Set(transform->GetPosition().x - spriteOrigin.x,
			transform->GetPosition().y + spriteSizeY * transScale.y - spriteOrigin.y);

		vertices[2].Set(transform->GetPosition().x + spriteSizeX * transScale.x - spriteOrigin.x,
			transform->GetPosition().y + spriteSizeY * transScale.y - spriteOrigin.y);

		vertices[3].Set(transform->GetPosition().x + spriteSizeX * transScale.x - spriteOrigin.x,
			transform->GetPosition().y - spriteOrigin.y);

		shape.Set(vertices, 4);
	}
}


void ce::Collider::FitSprite()
{
	fitSprite = true;

	sprite = gameObject->GetComponent<ce::Sprite>();
	spriteSizeX = sprite->GetSprite()->getTexture()->getSize().x;
	spriteSizeY = sprite->GetSprite()->getTexture()->getSize().y;
	spriteOrigin = sprite->GetOrigin();

	b2Vec2 vertices[4];

	vertices[0].Set(transPos.x - spriteOrigin.x,
					transPos.y - spriteOrigin.y);

	vertices[1].Set(transPos.x - spriteOrigin.x,
					transPos.y + spriteSizeY * transScale.y - spriteOrigin.y);

	vertices[2].Set(transPos.x + spriteSizeX * transScale.x - spriteOrigin.x,
					transPos.y + spriteSizeY * transScale.y - spriteOrigin.y);

	vertices[3].Set(transPos.x + spriteSizeX * transScale.x - spriteOrigin.x,
					transPos.y - spriteOrigin.y);

	shape.Set(vertices, 4);

	ce::GameObject* object1 = new ce::GameObject();
	ce::GameObject* object2 = new ce::GameObject();
	ce::GameObject* object3 = new ce::GameObject();
	ce::GameObject* object4 = new ce::GameObject();

	object1->GetTransform()->SetPosition(transform->GetPosition().x - spriteOrigin.x,
										transform->GetPosition().y - spriteOrigin.y);
	object2->GetTransform()->SetPosition(transform->GetPosition().x - spriteOrigin.x,
										transform->GetPosition().y + spriteSizeY  * transScale.y - spriteOrigin.y);
	object3->GetTransform()->SetPosition(transform->GetPosition().x + spriteSizeX * transScale.x - spriteOrigin.x,
										transform->GetPosition().y + spriteSizeY * transScale.y - spriteOrigin.y);
	object4->GetTransform()->SetPosition(transform->GetPosition().x + spriteSizeX * transScale.x - spriteOrigin.x,
										transform->GetPosition().y - spriteOrigin.y);

	ce::Sprite* sprite1 = object1->AddComponent<ce::Sprite>();
	ce::Sprite* sprite2 = object2->AddComponent<ce::Sprite>();
	ce::Sprite* sprite3 = object3->AddComponent<ce::Sprite>();
	ce::Sprite* sprite4 = object4->AddComponent<ce::Sprite>();

	sprite1->SetSprite("dot.png");
	sprite2->SetSprite("dot.png");
	sprite3->SetSprite("dot.png");
	sprite4->SetSprite("dot.png");
}


void ce::Collider::SetGameObject(GameObject * gameObject)
{
	transform = gameObject->GetTransform();
	transPos = transform->GetPosition();
	transScale = transform->GetScale();
}
