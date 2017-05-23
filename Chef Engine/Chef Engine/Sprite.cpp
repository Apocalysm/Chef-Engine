#include "Sprite.h"

#include "GameObject.h"
#include "DrawEventManager.h"

using ce::Sprite;

Sprite::Sprite()
{
	sprite = new sf::Sprite();

	drawOrder = 0;

	isNew = true;
}


Sprite::Sprite(const int newDrawOrder)
{
	sprite = new sf::Sprite();

	drawOrder = newDrawOrder;

	isNew = true;
}


Sprite::~Sprite()
{
	ce::DrawEventManager::RemoveSprite(this);
	delete sprite;
}


void Sprite::Update()
{
	// Updates psition, scale and rotation depending on the set values in the transform
	sprite->setPosition(transform->GetPosition());
	sprite->setRotation(transform->GetRotation());
	sprite->setScale(transform->GetScale());
}


void Sprite::SetSprite(const std::string& fileName)
{
	texture.loadFromFile(fileName);

	sprite->setTexture(texture);

	sprite->setPosition(transform->GetPosition());
}

void ce::Sprite::ChangeSprite(sf::Sprite* sprite)
{
	delete this->sprite; 
	this->sprite = sprite;
}


void Sprite::SetOrigin(const float x, const float y)
{
	sprite->setOrigin(x, y);
}


void Sprite::SetOrigin(const sf::Vector2f newOrigin)
{
	sprite->setOrigin(newOrigin);
}


void Sprite::SetColor(const sf::Color color)
{
	sprite->setColor(color);
}


void Sprite::SetColor(const int r, const int g, const int b, const int a)
{
	sprite->setColor(sf::Color(r, g, b, a));
}


void Sprite::SetDrawOrder(const int newDrawOrder)
{
    ce::DrawEventManager::MoveSprite(this, newDrawOrder);

	drawOrder = newDrawOrder;
}


sf::Sprite* Sprite::GetSprite() const
{
	return sprite;
}


sf::Vector2f Sprite::GetOrigin() const
{
	return sprite->getOrigin();
}


sf::Color Sprite::GetColor() const
{
	return sprite->getColor();
}


int Sprite::GetDrawOrder() const
{
	return drawOrder;
}


void ce::Sprite::SetGameObject(GameObject* gameObject)
{
	this->gameObject = gameObject;

	// Gets the transform of the owner of this sprite-component
	transform = gameObject->GetTransform();
	
	ce::DrawEventManager::AddSprite(this);
}


void Sprite::DoBind(lua_State * L)
{
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Chef")
			.deriveClass<Sprite, Component>("Sprite")
				.addConstructor<void(*)(void)>()
                .addFunction("SetSprite", &Sprite::SetSprite)
				.addProperty("sprite", &Sprite::GetSprite, &Sprite::ChangeSprite)
				
                .addProperty("position", &Sprite::GetPosition, &Sprite::SetPosition)
				.addProperty("scale", &Sprite::GetScale, &Sprite::SetScale)
				.addProperty("rotation", &Sprite::GetRotation, &Sprite::SetRotation)
				.addProperty("origin", &Sprite::GetOrigin, &Sprite::SetOrigin)

				.addProperty("color", &Sprite::GetColor, &Sprite::SetColor)
				.addProperty("drawOrder", &Sprite::GetDrawOrder, &Sprite::SetDrawOrder)
			.endClass()
		.endNamespace();
}