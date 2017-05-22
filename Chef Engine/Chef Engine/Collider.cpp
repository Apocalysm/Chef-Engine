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
	b2Vec2 center;

	transPos = transform->GetPosition();

	transRot = (transform->GetRotation() * PI) / 180;

	transScale = transform->GetScale();

	if (fitSprite)
	{
		float sprCenterX = transPos.x + spriteSizeX / 2 * transScale.x - spriteOrigin.x * transScale.x;
		float sprCenterY = transPos.y + spriteSizeY / 2 * transScale.y - spriteOrigin.y * transScale.y;
	
		center = b2Vec2(sprCenterX, sprCenterY);
	}
	else
	{
		center = b2Vec2(transPos.x, transPos.y);
	}
						
	body->SetTransform(center, transRot);

	/*ce::GameObject* obj = new ce::GameObject();
	ce::Sprite* spr = obj->AddComponent<ce::Sprite>();
	spr->SetSprite("dot.png");
	spr->SetDrawOrder(3);
	obj->GetTransform()->SetPosition(body->GetFixtureList()->GetAABB(0).GetCenter().x,
		body->GetFixtureList()->GetAABB(0).GetCenter().y);*/
}


void ce::Collider::SetupTMX(const sf::RectangleShape* rectShape, const bool dynamic, const bool isTrigger)
{
	fitSprite = false;

	if (dynamic)
		bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(rectShape->getPosition().x, rectShape->getPosition().y);
	body = CollisionManager::GetWorld()->CreateBody(&bodyDef);

	transScale = transform->GetScale();
	transRot = transform->GetRotation();

	b2Vec2 center = b2Vec2(rectShape->getSize().x / 2, rectShape->getSize().y / 2);

	shape.SetAsBox(rectShape->getSize().x * transScale.x / 2, 
				   rectShape->getSize().y * transScale.y / 2, center, transRot);

	body->SetSleepingAllowed(false);

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

	body->GetFixtureList()->SetSensor(isTrigger);
}


void ce::Collider::SetFitSprite(const bool fitSprite, const bool dynamic, const bool isTrigger)
{
	this->fitSprite = fitSprite;

	transPos = transform->GetPosition();
	transScale = transform->GetScale();
	transRot = (transform->GetRotation() * PI) / 180;

	sprite = gameObject->GetComponent<ce::Sprite>();
	spriteSizeX = sprite->GetSprite()->getTexture()->getSize().x;
	spriteSizeY = sprite->GetSprite()->getTexture()->getSize().y;
	spriteOrigin = sprite->GetOrigin();

	if(dynamic)
		bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(transPos.x, transPos.y);
	body = CollisionManager::GetWorld()->CreateBody(&bodyDef);

	shape.SetAsBox(spriteSizeX * transScale.x / 2, spriteSizeY * transScale.y / 2);

	body->SetSleepingAllowed(false);

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

	body->GetFixtureList()->SetSensor(isTrigger);

	/*ce::GameObject* obj = new ce::GameObject();
	ce::Sprite* spr = obj->AddComponent<ce::Sprite>();
	spr->SetSprite("dot.png");
	spr->SetDrawOrder(3);
	obj->GetTransform()->SetPosition(body->GetFixtureList()->GetAABB(0).GetCenter().x,
									 body->GetFixtureList()->GetAABB(0).GetCenter().y);*/

	/*ce::GameObject* obj2 = new ce::GameObject();
	ce::Sprite* spr2 = obj2->AddComponent<ce::Sprite>();
	spr2->SetSprite("dot.png");
	spr2->SetDrawOrder(3);
	obj2->GetTransform()->SetPosition(body->GetFixtureList()->GetAABB(1).GetCenter().x,
		body->GetFixtureList()->GetAABB(1).GetCenter().y);

	ce::GameObject* obj3 = new ce::GameObject();
	ce::Sprite* spr3 = obj3->AddComponent<ce::Sprite>();
	spr3->SetSprite("dot.png");
	spr3->SetDrawOrder(3);
	obj3->GetTransform()->SetPosition(body->GetFixtureList()->GetAABB(2).GetCenter().x,
		body->GetFixtureList()->GetAABB(2).GetCenter().y);

	ce::GameObject* obj4 = new ce::GameObject();
	ce::Sprite* spr4 = obj4->AddComponent<ce::Sprite>();
	spr4->SetSprite("dot.png");
	spr4->SetDrawOrder(3);
	obj4->GetTransform()->SetPosition(body->GetFixtureList()->GetAABB(3).GetCenter().x,
		body->GetFixtureList()->GetAABB(3).GetCenter().y);*/
}


void ce::Collider::SetIsTrigger(const bool isTrigger)
{
	body->GetFixtureList()->SetSensor(isTrigger);
}


bool ce::Collider::GetIsTrigger() const
{
	return body->GetFixtureList()->IsSensor();
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


void ce::Collider::OnCollision(Collider* other)
{
	std::cout << "Collision" << std::endl;
}


void ce::Collider::OnTrigger(Collider* other)
{
	std::cout << "Trigger" << std::endl;
}
