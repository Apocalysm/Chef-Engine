#include "Sprite.h"

#include "GameObject.h"
#include "DrawEventManager.h"

using ce::Sprite;

Sprite::Sprite()
{
	sprite = new sf::Sprite();
}


Sprite::Sprite(const std::string& fileName, const int newDrawOrder)
{
	sprite = new sf::Sprite();

	//SetSprite(fileName);

	drawOrder = newDrawOrder;
}


Sprite::~Sprite()
{
	ce::DrawEventManager::RemoveSprite(this);
	delete sprite;
}


void Sprite::Update()
{
	// Updates psition, scale and rotation depending on the set values in the transform
	sprite->setPosition(transform->GetPosition() + position);
	sprite->setScale(transform->GetScale() + scale);
	sprite->setRotation(transform->GetRotation() + rotation);
}


void Sprite::SetSprite(const std::string& fileName)
{
	texture.loadFromFile(fileName);

	sprite->setTexture(texture);

	sprite->setPosition(transform->GetPosition());
}

void ce::Sprite::ChangeSprite(sf::Sprite * sprite)
{
	delete this->sprite; 
	this->sprite = sprite;
}


void Sprite::SetPosition(const float x, const float y)
{
	position = sf::Vector2f(x, y);
}


void ce::Sprite::SetPosition(const sf::Vector2f newPosition)
{
	position = newPosition;
}


void Sprite::SetScale(const float x, const float y)
{
	//sprite.setScale(x, y);
	scale = sf::Vector2f(x, y);
}


void Sprite::SetScale(const sf::Vector2f newScale)
{
	//sprite.setScale(newScale);
	scale = newScale;
}


void Sprite::SetOrigin(const float x, const float y)
{
	sprite->setOrigin(x, y);
}


void Sprite::SetOrigin(const sf::Vector2f newOrigin)
{
	sprite->setOrigin(newOrigin);
}


void Sprite::SetRotation(const float angle)
{
	//sprite.setRotation(angle);
	rotation = angle;
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
	drawOrder = newDrawOrder;
}


sf::Sprite* Sprite::GetSprite() const
{
	return sprite;
}


sf::Vector2f Sprite::GetPosition() const
{
	return position;
}


sf::Vector2f Sprite::GetScale() const
{
	//return sprite.getScale();
	return scale;
}


sf::Vector2f Sprite::GetOrigin() const
{
	return sprite->getOrigin();
}


float Sprite::GetRotation() const
{
	//return sprite.getRotation();
	return rotation;
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