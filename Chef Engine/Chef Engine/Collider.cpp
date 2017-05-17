#include "Collider.h"
#include "GameObject.h"
#include "Sprite.h"
#include "CollisionManager.h"

using ce::Collider;


Collider::Collider() : transPos(sf::Vector2f(0.0f, 0.0f)), transScale(sf::Vector2f(0.0f, 0.0f)), spriteOrigin(sf::Vector2f(0.0f, 0.0f))
{
	fitSprite = false;
	isNew = true;
}


Collider::~Collider()
{
}


void ce::Collider::Update()
{
	if (fitSprite)
	{
		//fRect = sprite->getGlobalBounds();

		/*shape.setPosition(sprite->getPosition());
		shape.setRotation(sprite->getRotation());
		shape.setScale(sprite->getScale());
		shape.setOrigin(sprite->getOrigin());*/

		/*b2Vec2 vertices[4];

		vertices[0].Set(transform->GetPosition().x - spriteOrigin.x,
			transform->GetPosition().y - spriteOrigin.y);

		vertices[1].Set(transform->GetPosition().x - spriteOrigin.x,
			transform->GetPosition().y + spriteSizeY * transScale.y - spriteOrigin.y);

		vertices[2].Set(transform->GetPosition().x + spriteSizeX * transScale.x - spriteOrigin.x,
			transform->GetPosition().y + spriteSizeY * transScale.y - spriteOrigin.y);

		vertices[3].Set(transform->GetPosition().x + spriteSizeX * transScale.x - spriteOrigin.x,
			transform->GetPosition().y - spriteOrigin.y);

		shape.Set(vertices, 4);*/
	}
	else
	{
		//fRect = shape->getGlobalBounds();
	}

	/*deltaPos = transform->GetPosition() - lastPos;
	lastPos = transform->GetPosition();*/
	
	b2Vec2 transformPos;
	transformPos.x = transform->GetPosition().x;
	transformPos.y = transform->GetPosition().y;
	//body->SetTransform(transformPos, transform->GetRotation());
	body->SetTransform(body->GetPosition(), transform->GetRotation());
}


void ce::Collider::SetupTMX(sf::RectangleShape* rectShape)
{
	//fRect = rectShape->getGlobalBounds();
}


void ce::Collider::SetFitSprite(bool fitSprite, bool dynamic)
{
	this->fitSprite = fitSprite;

	if (fitSprite)
	{
		/*sprite = gameObject->GetComponent<ce::Sprite>()->GetSprite();

		fRect = sprite->getGlobalBounds();*/

		/*size.x = sprite->getTexture()->getSize().x;
		size.y = sprite->getTexture()->getSize().y;

		shape.setSize(size);
		shape.setPosition(sprite->getPosition());
		shape.setRotation(sprite->getRotation());
		shape.setScale(sprite->getScale());
		shape.setOrigin(sprite->getOrigin());*/
	}
	else
	{
		/*shape->setPosition(transform->GetPosition());
		shape->setRotation(transform->GetRotation());
		shape->setScale(transform->GetScale());

		fRect = shape->getGlobalBounds();*/
	}

	sprite = gameObject->GetComponent<ce::Sprite>();
	spriteSizeX = sprite->GetSprite()->getTexture()->getSize().x;
	spriteSizeY = sprite->GetSprite()->getTexture()->getSize().y;
	spriteOrigin = sprite->GetOrigin();

	/*b2Vec2 vertices[4];

	vertices[0].Set(transPos.x - spriteOrigin.x,
					transPos.y - spriteOrigin.y);

	vertices[1].Set(transPos.x - spriteOrigin.x,
					transPos.y + spriteSizeY * transScale.y - spriteOrigin.y);

	vertices[2].Set(transPos.x + spriteSizeX * transScale.x - spriteOrigin.x,
					transPos.y + spriteSizeY * transScale.y - spriteOrigin.y);

	vertices[3].Set(transPos.x + spriteSizeX * transScale.x - spriteOrigin.x,
					transPos.y - spriteOrigin.y);

	shape.Set(vertices, 4);*/

	if(dynamic)
		bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(transPos.x, transPos.y);
	body = CollisionManager::GetWorld()->CreateBody(&bodyDef);

	transPos = transform->GetPosition();

	b2Vec2 spriteCenter = b2Vec2(transPos.x + spriteSizeX / 2 - spriteOrigin.x,
		transPos.y + spriteSizeY / 2 - spriteOrigin.y);

	transRot = (transform->GetRotation() * PI) / 180;

	shape.SetAsBox(spriteSizeX / 2, spriteSizeY / 2);

	body->SetLinearDamping(0.1f);

	if (dynamic)
	{
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;

		body->CreateFixture(&fixtureDef);
	}
	else
		body->CreateFixture(&shape, 0.0f);

	/*ce::GameObject* object1 = new ce::GameObject();
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
	sprite4->SetSprite("dot.png");*/
}


//void ce::Collider::SetSize(const float x, const float y)
//{
//	size = sf::Vector2f(x, y);
//	shape->setSize(size);
//}
//
//
//sf::Vector2f ce::Collider::GetSize() const
//{
//	return shape->getSize();
//}
//
//
//void ce::Collider::SetOrigin(float x, float y)
//{
//	shape->setOrigin(x, y);
//}
//
//
//sf::Vector2f ce::Collider::GetOrigin() const
//{
//	return shape->getOrigin();
//}


void ce::Collider::SetIsTrigger(bool isTrigger)
{
	this->isTrigger = isTrigger;
}


bool ce::Collider::GetIsTrigger() const
{
	return isTrigger;
}


void ce::Collider::SetGameObject(GameObject * gameObject)
{
	this->gameObject = gameObject;

	transform = gameObject->GetTransform();

	//lastPos = transform->GetPosition();

	ce::CollisionManager::AddCollider(this);

	transform = gameObject->GetTransform();
	transPos = transform->GetPosition();
	transScale = transform->GetScale();;
}


void ce::Collider::OnCollision(GameObject * other)
{
	//std::cout << "Collision" << std::endl;
}


void ce::Collider::OnTrigger(GameObject * other)
{
	std::cout << "Trigger" << std::endl;
}
