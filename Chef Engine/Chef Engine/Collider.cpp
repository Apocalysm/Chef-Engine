#include "Collider.h"
#include "GameObject.h"
#include "Sprite.h"
#include "CollisionManager.h"

using ce::Collider;


Collider::Collider()
{
}


Collider::~Collider()
{
	ce::CollisionManager::RemoveCollider(this);
}


void ce::Collider::Update()
{
	// Position that the body should be at
	b2Vec2 center;

	transPos = transform->GetPosition();

	// Gets rotation of the transform and calculates it from degrees to radians
	transRot = (transform->GetRotation() * PI) / 180;

	transScale = transform->GetScale();

	// If the collision box should fit a sprite
	if (fitSprite)
	{
		// Calculates the position of the sprites center on screen
		float sprCenterX = transPos.x + spriteSizeX / 2 * transScale.x - spriteOrigin.x * transScale.x;
		float sprCenterY = transPos.y + spriteSizeY / 2 * transScale.y - spriteOrigin.y * transScale.y;
	
		center = b2Vec2(sprCenterX, sprCenterY);
	}
	else
	{
		center = b2Vec2(transPos.x, transPos.y);
	}
						
	body->SetTransform(center, transRot);
}


void ce::Collider::SetupTMX(const sf::Vector2f rectSize, const bool dynamic, const bool isTrigger)
{
	fitSprite = false;

	// Makes bodies created from the bodyDef dynamic 
	if (dynamic)
		bodyDef.type = b2_dynamicBody;

	// Creates a body and adds it to the world
	body = CollisionManager::GetWorld()->CreateBody(&bodyDef);

	// The body will now hold a pointer to this component
	body->SetUserData(this);

	transScale = transform->GetScale();

	// Gets rotation of the transform and calculates it from degrees to radians
	transRot = (transform->GetRotation() * PI) / 180;

	// Sets origin of the body so that it will be in the central position of the box in Tiled
	b2Vec2 center = b2Vec2(rectSize.x / 2, rectSize.y / 2);

	// Makes the shape a box based on size of the box, the scale of the transform, the center of the Tiled box and the rotation of the transform
	shape.SetAsBox(rectSize.x * transScale.x / 2, rectSize.y * transScale.y / 2, center, transRot);

	// The body will never "sleep" so that physics will always affect the body
	body->SetSleepingAllowed(false);

	// If the body is dynamic
	if (dynamic)
	{
		// Physics will no longer affect rotation
		body->SetFixedRotation(true);

		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;

		// Creates a fixture that is aplied to the body
		body->CreateFixture(&fixtureDef);
	}
	else
		// Creates a fixture that is aplied to the body
		body->CreateFixture(&shape, 0.0f);

	// Makes the body a sensor or not based on if it should be
	// Sensor is basically the same as Trigger in Unity
	body->GetFixtureList()->SetSensor(isTrigger);

	bodyIsCreated = true;
}


void ce::Collider::SetFitSprite(const bool fitSprite, const bool dynamic, const bool isTrigger)
{
	this->fitSprite = fitSprite;

	// If a body hasn't been created already
	if (!bodyIsCreated)
	{
		// Gets tranform info
		transPos = transform->GetPosition();
		transScale = transform->GetScale();
		// Gets rotation of the transform and calculates it from degrees to radians
		transRot = (transform->GetRotation() * PI) / 180;

		// Gets the sprite component and it's relevant info
		sprite = gameObject->GetComponent<ce::Sprite>();
		spriteSizeX = sprite->GetSprite()->getTexture()->getSize().x;
		spriteSizeY = sprite->GetSprite()->getTexture()->getSize().y;
		spriteOrigin = sprite->GetOrigin();

		// Makes bodies created from the bodyDef dynamic 
		if (dynamic)
			bodyDef.type = b2_dynamicBody;

		bodyDef.position.Set(transPos.x, transPos.y);

		// Creates a body and adds it to the world
		body = CollisionManager::GetWorld()->CreateBody(&bodyDef);

		// The body will now hold a pointer to this component
		body->SetUserData(this);

		// Makes the shape a box based on size of the sprite and the scale of the transform
		shape.SetAsBox(spriteSizeX * transScale.x / 2, spriteSizeY * transScale.y / 2);

		// The body will never "sleep" so that physics will always affect the body
		body->SetSleepingAllowed(false);

		// If the body is dynamic
		if (dynamic)
		{
			// Physics will no longer affect rotation
			body->SetFixedRotation(true);

			fixtureDef.shape = &shape;
			fixtureDef.density = 1.0f;
			fixtureDef.friction = 0.3f;

			// Creates a fixture that is aplied to the body
			body->CreateFixture(&fixtureDef);
		}
		else
			// Creates a fixture that is aplied to the body
			body->CreateFixture(&shape, 0.0f);

		// Makes the body a sensor or not based on if it should be
		// Sensor is basically the same as Trigger in Unity
		body->GetFixtureList()->SetSensor(isTrigger);

		bodyIsCreated = true;
	}
}


void ce::Collider::SetIsTrigger(const bool isTrigger)
{
	this->isTrigger = isTrigger;
	body->GetFixtureList()->SetSensor(isTrigger);
}


bool ce::Collider::GetIsTrigger() const
{
	return isTrigger;
}


void ce::Collider::SetGameObject(GameObject * gameObject)
{
	this->gameObject = gameObject;

	transform = gameObject->GetTransform();

	// Adds this collider to the CollisionManager
	ce::CollisionManager::AddCollider(this);
}


void ce::Collider::OnCollisionEnter(Collider* other)
{
	collidingColls.insert(std::make_pair(other->gameObject->GetID(), other));
	std::cout << "Collision Enter" << std::endl;
}


void ce::Collider::OnCollisionExit(Collider* other)
{
	
	std::cout << "Collision Exit" << std::endl;
}


void ce::Collider::OnCollisionStay(Collider* other)
{
	std::cout << "Collision Stay" << std::endl;
}


void ce::Collider::OnTriggerEnter(Collider* other)
{
	std::cout << "Trigger Enter" << std::endl;
}


void ce::Collider::OnTriggerExit(Collider* other)
{
	std::cout << "Trigger Exit" << std::endl;
}


void ce::Collider::OnTriggerStay(Collider * other)
{
	std::cout << "Trigger Stay" << std::endl;
}


void Collider::DoBind(lua_State * L)
{
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Chef")
			.beginClass<Collider>("Collider")
				.addFunction("SetFitSprite", &Collider::SetFitSprite)
				.addProperty("isTrigger", &Collider::GetIsTrigger, &Collider::SetIsTrigger)
			.endClass()
		.endNamespace();
}