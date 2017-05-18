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
	}
	
	/*b2Vec2 transformPos;
	transformPos.x = transform->GetPosition().x;
	transformPos.y = transform->GetPosition().y;
	transRot = (transform->GetRotation() * PI) / 180;
	body->SetTransform(transformPos, transRot);*/

	b2Vec2 spritePos = b2Vec2(sprite->GetSprite()->getPosition().x - sprite->GetOrigin().x,
							  sprite->GetSprite()->getPosition().y - sprite->GetOrigin().y);
	transRot = (transform->GetRotation() * PI) / 180;
	body->SetTransform(spritePos, transRot);
}


void ce::Collider::SetupTMX(sf::RectangleShape* rectShape)
{
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

	/*b2Vec2 spriteCenter = b2Vec2(transPos.x + spriteSizeX / 2 - spriteOrigin.x,
		transPos.y + spriteSizeY / 2 - spriteOrigin.y);*/

	b2Vec2 center = b2Vec2(-spriteSizeX / 2 + spriteOrigin.x, -spriteSizeY / 2 + spriteOrigin.y);

	transRot = (transform->GetRotation() * PI) / 180;

	shape.SetAsBox(spriteSizeX / 2, spriteSizeY / 2);
	//shape.SetAsBox(spriteSizeX / 2, spriteSizeY / 2, center, transRot);

	//body->SetLinearDamping(0.1f);

	body->SetSleepingAllowed(false);

	b2MassData* massData = new b2MassData();
	body->GetMassData(massData);
	massData->center.Set(center.x, center.y);
	body->SetMassData(massData);



	if (dynamic)
	{
		body->SetFixedRotation(true);

		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;

		body->CreateFixture(&fixtureDef);
	}
	else
		body->CreateFixture(&shape, 0.0f);

	body->SetMassData(massData);
}


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
